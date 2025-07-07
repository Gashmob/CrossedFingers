{
  description = "Crossed Fingers 🤞 dev environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

    yeschief = {
      url = "github:Gashmob/YesChief/v1.1.2";
      inputs.nixpkgs.follows = "nixpkgs";
    };

    # <https://github.com/nix-systems/nix-systems>
    systems.url = "github:nix-systems/default-linux";
  };

  outputs = { nixpkgs, yeschief, systems, ... }:
    let
      eachSystem = nixpkgs.lib.genAttrs (import systems);
      pkgs = eachSystem (system: import nixpkgs { inherit system; });
      pnpm = eachSystem (system:
        pkgs.${system}.pnpm.override {
          version = "10.12.4";
          hash = "sha256-yt/Z5sn8wst2/nwHeaUlC2MomK6l9T2DOnNpDHeneNk=";
          nodejs = pkgs.${system}.nodejs_20;
        });

      crossedfingers-package = eachSystem (system:
        pkgs.${system}.callPackage ./crossedfingers.nix {
          yeschief = yeschief.packages.${system}.yeschief;
        });
    in {
      packages = eachSystem (system: {
        crossedfingers = crossedfingers-package.${system};
        default = crossedfingers-package.${system};
      });

      devShells = eachSystem (system: {
        default = pkgs.${system}.mkShellNoCC {
          name = "crossedfingers-dev-env";

          packages = with pkgs.${system};
            [ git cmake ninja clang dpkg rpm nodejs_20 doxygen ]
            ++ [ pnpm.${system} yeschief.packages.${system}.yeschief ];

          shellHook = ''
            export ROOT_DIR=$(git rev-parse --show-toplevel)
            export PATH="$PATH:$ROOT_DIR/tools/bin"
            pnpm install;
            echo -e "\n\033[34mWelcome to \033[1mCrossed Fingers 🤞\033[0m\033[34m dev environment\033[0m\n"
          '';
        };
      });
    };
}
