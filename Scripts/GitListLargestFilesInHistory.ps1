﻿# Get all object-hashes and paths
  $objects = git rev-list --objects --all | Out-String -Stream

# Use batch-check to get all sizes in a row
  $batchInput = $objects | ForEach-Object { ($_ -split ' ')[0] } | Out-String
  $sizeOutput = $batchInput | git cat-file --batch-check | Out-String -Stream

# Define the extensions to ignore
  $ignoredExtensions = @('h', 'hpp', 'cpp', 'ixx', 'cxx')

# Combine path, hash, size and sort them by the larges
  $combined = $objects | ForEach-Object -Begin {
    $index = 0
  } -Process {
    $line = $_ -split ' '
    $path = $line[1]
    
    # Check if the file extension should be ignored
    $extension = [System.IO.Path]::GetExtension($path).TrimStart('.').ToLower()
      if ($ignoredExtensions -notcontains $extension) {
      $sizeInfo = $sizeOutput[$index] -split ' '
      $hash = $sizeInfo[0]
      $size = $sizeInfo[2] -as [int]
      [PSCustomObject]@{ Hash = $hash; Path = $path; Size = $size }
    }

    $index++
  } | Sort-Object Size -Descending | Select-Object -First 128

# Output
  $combined | Format-Table -AutoSize