# Dev shell for building kernel modules against the RUNNING NixOS kernel.
let
  pkgs = import <nixpkgs> {};
  # Uses your system's own config, so the kernel matches `uname -r`
  # (assuming you've rebooted into your latest generation).
  nixos = import <nixpkgs/nixos> {};
  kernel = nixos.config.boot.kernelPackages.kernel;
in
pkgs.mkShell {
  nativeBuildInputs = kernel.moduleBuildDependencies ++ [ pkgs.gnumake ];
  KDIR = "${kernel.dev}/lib/modules/${kernel.modDirVersion}/build";
  shellHook = ''
    echo "Kernel (running): $(uname -r)"
    echo "Kernel (headers): ${kernel.modDirVersion}"
    echo "KDIR=$KDIR"
  '';
}
