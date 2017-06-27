#!/usr/bin/python2.7
import os, sys, shutil, platform, time

OUTPUT = ""
SOURCE = None

VERSIONS = 1

__OUTPUT = "bin/conf0%s"
COMPILER = "gcc"
INCLUDE = [ ]
__SOURCE = [
  "src/0%s/*.c",
  "src/0%s/lib/fs/*.c",
]
FLAGS = [ "-Wall", "-Wextra","--std=c99" ]
LINK = [ "m" ]
DEFINE = [ ]
EXTRA = ""

if platform.system() == "Windows":
  OUTPUT += ".exe"
  LINK += [ "mingw32" ]
  FLAGS += [ "-mwindows" ]

if platform.system() == "Linux":
  LINK += [  ]

if platform.system() == "Darwin":
  LINK += [ ]
  FLAGS += [ ]
  DEFINE += [ ]


def fmt(fmt, dic):
  for k in dic:
    fmt = fmt.replace("{" + k + "}", str(dic[k]))
  return fmt

def clearup():
  if os.path.isfile(OUTPUT):
    os.remove(OUTPUT)

def main():
  global FLAGS, SOURCE, LINK
  for i in range(VERSIONS + 1):
    OUTPUT = __OUTPUT % i
    SOURCE = [  ]
    for j in range(len(__SOURCE)):
      SOURCE += [ __SOURCE[j] % i ]

    print "[conf0%d] initing..." % i
    starttime = time.time()
    clearup()

    # Handle args
    build = "debug" if "debug" in sys.argv else "release"
    verbose = "verbose" in sys.argv

    # Handle build type
    if build == "debug":
      FLAGS += [ "-g" ]
    else:
      FLAGS += [ "-O3" ]

    print ("[conf0%d] building (" % i) + build + ")..."

    # Make sure there arn't any temp files left over from a previous build

    # Create directories
    outdir = os.path.dirname(OUTPUT)
    if not os.path.exists(outdir):
      os.makedirs(outdir)

    # Build
    cmd = fmt(
      "{compiler} -o {output} {flags} {source} {include} {link} {define} " +
      "{extra}",
      {
        "compiler"  : COMPILER,
        "output"    : OUTPUT,
        "source"    : " ".join(SOURCE),
        "include"   : " ".join(map(lambda x:"-I" + x, INCLUDE)),
        "link"      : " ".join(map(lambda x:"-l" + x, LINK)),
        "define"    : " ".join(map(lambda x:"-D" + x, DEFINE)),
        "flags"     : " ".join(FLAGS),
        "extra"     : EXTRA,
      })

    if verbose:
      print cmd

    print "[conf0%d] compiling..." % i
    res = os.system(cmd)

    if build == "release" and os.path.isfile(OUTPUT):
      print "[conf0%d] stripping..." % i
      os.system("strip %s" % OUTPUT)

    if res == 0:
      print "[conf0%d] done (%.2fs)" % (i, time.time() - starttime)
    else:
      print "[conf0%d] done with errors" % i
  sys.exit(res)


if __name__ == "__main__":
  main()