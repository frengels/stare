{ nixpkgs ? <nixpkgs> }:
let
    pkgs = import nixpkgs { };

    jobs = rec {
        nix = pkgs.callPackage ./derivation.nix { };
        # gcc8 is not supported because it does not properly display automatically reflected enum entries
        # this could be solved by simply turning off automatic reflection of enums
        nix-gcc9 = pkgs.callPackage ./derivation.nix { stdenv = pkgs.gcc9Stdenv; };
        nix-gcc10 = pkgs.callPackage ./derivation.nix { stdenv = pkgs.gcc10Stdenv; };

        nix-clang_10 = pkgs.callPackage ./derivation.nix { stdenv = with pkgs; overrideCC stdenv clang_10; };
    };
in
    jobs
