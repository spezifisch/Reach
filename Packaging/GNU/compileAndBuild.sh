#!/bin/bash -ex
# GNU BUILD SCRIPT

project=Reach
version=1.5.0
xmlFile=Reach

build_standalone=0
build_plugin=1
build_installer=0
do_cleanup=0

src_dir=$HOME
workspace="$src_dir"/Reach
hise_base="$src_dir"/HISE
hise_path="$src_dir"/HISE/projects/standalone/Builds/LinuxMakefile/build/HISE\ Standalone
projucer_path="$src_dir"/HISE/tools/projucer/Projucer
makeself="$src_dir"/makeself

#Create temp directory for packaging
package="$workspace"/Packaging/GNU/temp
mkdir -p "$package"

mkdir -p "$workspace"/Binaries
cd "$workspace"/Binaries || exit 1

# STEP 1: BUILDING THE BINARIES
# ====================================================================
if ((build_standalone == 1 || build_plugin == 1))
then

  "$hise_path" set_hise_folder -p:"$hise_base"
  "$hise_path" set_project_folder -p:"$workspace"
  "$hise_path" set_version -v:$version

  echo Making the Projucer accessible for this project
  chmod +x "$projucer_path"

  if ((build_standalone==1))
  then
    echo Building the standalone app
    "$hise_path" clean -p:"$workspace" --all
    "$hise_path" export_ci XmlPresetBackups/$xmlFile.xml -t:standalone -a:x64

    bash -ex "$workspace"/Binaries/batchCompileLinux.sh

    cp "$workspace"/Binaries/Builds/LinuxMakefile/build/"$project" "$package"
  fi

  if ((build_plugin==1))
  then
    echo Building the plugins
    "$hise_path" clean -p:"$workspace" --all
    "$hise_path" export_ci XmlPresetBackups/$xmlFile.xml -t:instrument -p:VST -a:x64

    bash -ex "$workspace"/Binaries/batchCompileLinux.sh

    cp "$workspace"/Binaries/Builds/LinuxMakefile/build/"$project".so "$package"
  fi
fi

# STEP 2: BUILDING INSTALLER
# ====================================================================

if ((build_installer==1))
then
  echo "Build Installer"

  mkdir -p "$workspace"/Installer
  cp "$workspace"/License.txt "$package"
  cp "$workspace"/Packaging/GNU/GNUInstaller.sh "$package"

  #Run makeself
  sh "$makeself"/makeself.sh --license "$workspace"/License.txt "$workspace"/Packaging/GNU/temp "$workspace"/Installer/"$project"\ $version.sh "$project" ./GNUInstaller.sh

else
  echo "Skip Building Installer"
fi

if ((do_cleanup==1))
then
  echo Cleanup
  cd "$workspace" || exit 2
  rm -rf "$workspace"/Packaging/GNU/temp
else
  ls -l "$package"
fi
