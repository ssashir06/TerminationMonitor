#escape=`

FROM mcr.microsoft.com/windows/servercore:1809 AS builder
SHELL ["PowerShell.exe", "-Command", "$ErrorActionPreference = 'Stop'; $ProgressPreference = 'SilentlyContinue';"]
WORKDIR C:\SampleDir
ADD run.ps1 .
ADD TerminationMonitor.exe .

ENTRYPOINT PowerShell.exe -Command C:\SampleDir\run.ps1