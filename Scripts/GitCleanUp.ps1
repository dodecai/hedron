# Define paths to delete
  $pathsToDelete = @(
    "a",
    "b",
  )

# Run git filter-repo to delete paths
  for ($object in $objects) {
    git filter-repo --path $object --invert-paths
  }

# Repack the repository and prune unreachable objects
  #git reflog expire --expire=now --all
  #git gc --prune=now --aggressive