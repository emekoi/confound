import os, sys, shutil, platform, time

cmds = [ ]

def main():
  global cmds
  test_dir = sys.argv[1] if len(sys.argv) > 1 and os.path.isdir(sys.argv[1]) else "example"
  starttime = time.time()
  for subdir, dirs, files in os.walk(test_dir):
    for file in files:
    	cmds += [ "bin\\conf %s" % os.path.join(subdir, file) ]
  for cmd in cmds:
  	os.system(cmd)
  sys.exit(0)

if __name__ == "__main__":
  main()