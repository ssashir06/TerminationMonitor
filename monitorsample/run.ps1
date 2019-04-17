try {
    Write-Host Start app;
    $process = Start-Process notepad.exe -PassThru;
    Write-Host PID: $process.Id;
    Write-Host Monitor start;
    Get-Process;
    .\TerminationMonitor.exe $process.Id; 
    Write-Host Monitor ended;
    Get-Process;
}
finally {
    Write-Host Done.;
}