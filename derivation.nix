{ stdenv, cmake, doctest }:
stdenv.mkDerivation rec {
    name = "stare-${version}";
    version = "0.0.1";

    src = ./.;
    nativeBuildInputs = [ cmake doctest ];
    buildInputs = [];

    cmakeFlags = [ "-DSTARE_TESTS=ON" ];

    enableParallelBuilding = true;
    releaseName = name;

    doCheck = true;
    checkTarget = "test";

    meta = with stdenv.lib; {
        description = "Static reflection for c++20";
        homepage = https://github.com/dreyri/stare;
        license = licenses.mit;
        platforms = platforms.all;
    };
}