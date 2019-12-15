from distutils.core import setup, Extension
import os

def main():
    setup(name="cool",
          version="1.0.0",
          description="Python PiNAT library",
          author="Ofri Marx",
          author_email="ofrikm@gmail.com",
          ext_modules=[Extension("pynat", ["src/cpp/pynat.cpp", "src/cpp/pySniffer.cpp", "src/cpp/sniffer.cpp"], extra_compile_args=["-Wno-unused", "-Iexternals"], extra_link_args=["-L/home/magshimim/Documents/1402-pinat-/externals/", "-ltins"])])

if __name__ == "__main__":
    main()