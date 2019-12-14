from distutils.core import setup, Extension
import os

def main():
    setup(name="cool",
          version="1.0.0",
          description="Python PiNAT library",
          author="Ofri Marx",
          author_email="ofrikm@gmail.com",
          ext_modules=[Extension("pynat", ["src/pynat.cpp", "src/pySniffer.cpp", "src/sniffer.cpp"], extra_compile_args=["-Wno-unused"], extra_link_args=["-ltins"])])

if __name__ == "__main__":
    main()