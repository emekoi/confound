import os, sys, shutil, platform

cmds = [ ]
res = 0

def main():
  global cmds, res

  if os.path.isfile("bin/conf"):
    test_dir = sys.argv[1] if len(sys.argv) > 1 and os.path.isdir(sys.argv[1]) else "example"

    for subdir, dirs, files in os.walk(test_dir):
      for file in files:
        if platform.system() == "Windows":
          cmds += [ "bin\\conf %s" % os.path.join(subdir, file) ]
        else:
          cmds += [ "bin/conf %s" % os.path.join(subdir, file) ]

    # if platform.system() == "Windows":
    #   cmds += [ "bin\\conf example\\factor.bf" ]
    # else:
    #   cmds += [ "bin/conf example/factor.bf" ]

    for cmd in cmds:
      res += os.system(cmd)
    
  sys.exit(res)

if __name__ == "__main__":
  main()