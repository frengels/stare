self: super: {
    stare = self.callPackage ./derivation.nix { stdenv = self.gcc10Stdenv; };
}