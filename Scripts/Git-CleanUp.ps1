# Define paths to delete
  $pathsToDelete = @(
    "Assets/Models/Sponza",
    "test",
    "3rd-Party/LibPHX/ext/lib/win64"
  )

# Run git filter-repo to delete paths
  python git-filter-repo --path "${($pathsToDelete -join ' ')}" --invert-paths

# Repack the repository and prune unreachable objects
  git reflog expire --expire=now --all
  git gc --prune=now --aggressive