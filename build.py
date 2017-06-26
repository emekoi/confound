#!/usr/bin/python2.7
import os, sys, shutil, platform, time

OUTPUT = "bin/conf"
COMPILER = "gcc"
INCLUDE = [ ]
SOURCE = [
  "src/*.c",
  "src/lib/vec/*.c",
  "src/lib/fs/*.c",
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

  print "initing..."
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

  print "building (" + build + ")..."

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

  print "compiling..."
  res = os.system(cmd)

  if build == "release" and os.path.isfile("bin/conf"):
    print "stripping..."
    os.system("strip %s" % OUTPUT)

  if res == 0:
    print "done (%.2fs)" % (time.time() - starttime)
  else:
    print "done with errors"
  sys.exit(res)


if __name__ == "__main__":
  main()