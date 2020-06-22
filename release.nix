{ nixpkgs ? <nixpkgs> }:
let
    pkgs = import nixpkgs {config = {}; };
    pkgs-aarch64 = import nixpkgs { system="aarch64-linux"; config = {}; };

    jobs = rec {
        nix-gcc10 = pkgs.callPackage ./derivation.nix { stdenv = pkgs.gcc10Stdenv; };

        nix-clang_10 = pkgs.callPackage ./derivation.nix { stdenv = with pkgs; overrideCC stdenv clang_10; };

        nix-gcc10-aarch64 = pkgs-aarch64.callPackage ./derivation.nix { stdenv = pkgs-aarch64.gcc10Stdenv; };
    };
in
    jobs
