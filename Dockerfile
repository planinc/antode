FROM ubuntu:18.04

# Update software repository
RUN apt-get update
RUN apt-get install -y build-essential ca-certificates apt-utils autoconf # Essentials

# Install dependencies  ******************
# Utilities
RUN apt-get install -y cmake git wget graphviz zlib1g-dev libboost-all-dev

# Eigen3
RUN apt-get install -y libeigen3-dev

# gTests
RUN apt-get install -y libgtest-dev && \
    cd /usr/src/gtest && \
    cmake CMakeLists.txt && \
    make && \
    cp *.a /usr/lib

# Protobuf
RUN git clone https://github.com/protocolbuffers/protobuf.git && \
	cd protobuf && \
	git submodule update --init --recursive
RUN cd protobuf && \
    ./autogen.sh && \
	./configure && \
    make -j$(nproc) && \
    make install && \
    ldconfig

# Install development libraries
RUN apt-get install -y doxygen
RUN apt-get install -y python3-pip
RUN pip3 install sphinx
RUN pip3 install sphinx_rtd_theme
RUN pip3 install sphinx-tabs
RUN pip3 install breathe
# ****************** Install dependencies

# Set working directory
ENV EDDL_ROOT /eddl
WORKDIR $EDDL_ROOT

# Copy repo
COPY . .

# Build EDDL
RUN mkdir build
RUN cd build && \
    cmake .. -DBUILD_PROTOBUF=ON -DBUILD_EXAMPLES=ON -DBUILD_TESTS=ON && \
    make -j$(nproc) && \
    make install

# Test EDDL
RUN cd build && ctest --verbose

# Build docs (optional, check .dockerignore)
RUN cd docs/doxygen && doxygen
RUN cd docs/source && make clean && make html

