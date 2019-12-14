from distutils.core import setup, Extension
import os

def main():
    setup(name="cool",
          version="1.0.0",
          description="Python PiNAT library",
          author="Ofri Marx",
          author_email="ofrikm@gmail.com",
          ext_modules=[Extension("pynat", ["src/pynat.cpp", "src/pySniffer.cpp"], extra_compile_args=["-Wno-unused"], extra_link_args=["-ltins"])])

if __name__ == "__main__":
    main()
    os.system("cp build/lib.linux-x86_64-3.6/pynat.cpython-36m-x86_64-linux-gnu.so pynat.so && rm -rf build")