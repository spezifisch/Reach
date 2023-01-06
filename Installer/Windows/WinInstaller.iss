; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Reach"
#define MyAppVersion "1.3"
#define MyAppPublisher "Sinuslabs"
#define MyAppURL "https://sinuslabs.io"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{50390B08-02B5-4C74-9C0C-75E635B71015}
DisableWelcomePage=no
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
OutputDir=C:\Users\iso\Documents\GitHub\Reach\Installer\Windows\exe\
OutputBaseFilename=reach-installer
Compression=lzma
SolidCompression=yes
WizardStyle=modern
AppCopyright=2022 Sinuslabs
SetupIconFile=C:\Users\iso\Documents\GitHub\Reach\Installer\Windows\icon.ico
WizardImageFile=C:\Users\iso\Documents\GitHub\Reach\Installer\Windows\Wizard-image.bmp
DefaultDirName="C:\Program Files\Common Files\VST3\"
DisableDirPage=no
DirExistsWarning=no

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"; LicenseFile: "C:\Users\iso\Documents\GitHub\Reach\LICENSE"

[Files]
Source: "C:\Users\iso\Documents\GitHub\Reach\Binaries\Compiled\VST3\Reach.vst3"; DestDir: "C:\Program Files\Common Files\VST3\"; Flags: ignoreversion recursesubdirs createallsubdirs
