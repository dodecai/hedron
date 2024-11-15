# Define paths to delete
  $objects = @(
    "a",
    "b"
  )

# Run git filter-repo to delete paths
  foreach ($object in $objects) {
    git filter-repo --path $object --invert-paths --force
  }

# Repack the repository and prune unreachable objects
  #git reflog expire --expire=now --all
  #git gc --prune=now --aggressive