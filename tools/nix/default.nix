let
  pkgs = (import ./pin-nixpkgs.nix) {};
  yeschief = pkgs.callPackage ./yeschief.nix { };
in {
  crossedfingers = pkgs.callPackage ./crossedfingers.nix { yeschief = yeschief; };
}
