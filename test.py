import os, sys, shutil, platform, subprocess

res = 0
tests = [ ]
binary = "conf%s"

def main():
  global tests, res
  div = ""

  if platform.system() == "Windows":
    div = "\\"
  else:
    div = "/"

  for _subdir, _dirs, _files in os.walk("bin"):
    for _file in _files:
      bin = _subdir + div + _file
      if os.path.isfile(bin):
        for subdir, dirs, files in os.walk("example"):
          for file in files:
            # cmd = [ bin, os.path.join(subdir, file) ]
            # print bin, os.path.join(subdir, file)
            res += os.system(bin + " " + os.path.join(subdir, file))
            # res += subprocess.call(cmd)

  sys.exit(res)

if __name__ == "__main__":
  main()