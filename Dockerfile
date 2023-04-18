FROM ghcr.io/spezifisch/hise-builder:main-hise-3.0.3-ci-dsp

ARG REACH_VERSION="1.5.0"
ARG VST3_BUNDLE="Reach-v$REACH_VERSION-Linux-VST3.tar.gz"

COPY . /root/Reach/

# workaround for HISE segfault when it expects an X server due to the way -dsp flag is currently implemented
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get -y install \
    xvfb \
    && rm -rf /var/lib/apt/lists/*

# compile plugin
WORKDIR /root/Reach
RUN xvfb-run ./Packaging/GNU/compileAndBuild.sh

# bundle plugin
WORKDIR /root/Reach/Binaries/Builds/LinuxMakefile/build
RUN mkdir -p /output \
    && tar cfvz "/output/$VST3_BUNDLE" Reach.vst3 \
    && find /output -type f -exec sha256sum '{}' \;
