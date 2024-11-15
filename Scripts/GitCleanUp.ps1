# Define paths to delete
  $pathsToDelete = @(
    "a",
    "b",
  )

# Run git filter-repo to delete paths
  python git-filter-repo --path "${($pathsToDelete -join ' ')}" --invert-paths

# Repack the repository and prune unreachable objects
  git reflog expire --expire=now --all
  git gc --prune=now --aggressive