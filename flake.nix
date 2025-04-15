{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "nixpkgs/release-24.11";
  };

  outputs = { self, nixpkgs }: let
    supported_systems = [
      "x86_64-linux"
    ];

    for_all_systems = f: nixpkgs.lib.genAttrs supported_systems ( system: f {
      pkgs = import nixpkgs { inherit system; };
    });
  in
    {
    devShells = for_all_systems ({ pkgs }: {
      default = pkgs.mkShellNoCC {
        packages = with pkgs; [
          gcc-arm-embedded-13
          bear
          openocd
        ];
      };
    });

    packages = for_all_systems ({ pkgs }: {
      firmware = pkgs.stdenv.mkDerivation {
        name = "firmware";
        src = ./.;
        buildInputs = with pkgs; [
          gcc-arm-embedded-13
        ];
        installPhase = ''
          PREFIX="$out" make install
        '';
      };
    });
  };
}
