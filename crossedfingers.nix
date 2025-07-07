{ stdenv
, cmake
, ninja
, yeschief
}:

stdenv.mkDerivation {
  pname = "crossedfingers";
  version = builtins.readFile ./VERSION;

  src = ./.;

  nativeBuildInputs = [ cmake ninja ];
  buildInputs = [ yeschief ];
  cmakeFlags = [ "-DBUILD_TESTING=On" ];

  doCheck = true;
}
