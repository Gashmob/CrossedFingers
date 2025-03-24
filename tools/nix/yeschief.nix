{ stdenv
, fetchFromGitHub
, cmake
, ninja
}:

stdenv.mkDerivation rec {
  pname = "yeschief";
  version = "1.1.1";

  src = fetchFromGitHub {
    owner = "Gashmob";
    repo = "YesChief";
    rev = "v${version}";
    hash = "sha256-Zr2J4NnIKJzLcm66S+oFSOSICL56bPLrOk/NQZyaDFA=";
  };

  nativeBuildInputs = [ cmake ninja ];
}
