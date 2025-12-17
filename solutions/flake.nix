{
  description = "C/C++ tasks";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs =
    { self, nixpkgs }:
    let
      systems = [
        "x86_64-linux"
      ];
      forAllSystems = f: nixpkgs.lib.genAttrs systems (system: f system);
    in
    {
      packages = forAllSystems (
        system:
        let
          pkgs = import nixpkgs { inherit system; };
          clangStdenv = pkgs.llvmPackages_21.stdenv;

          root = ./.;
          dirEntries = builtins.readDir root;

          taskDirs = pkgs.lib.filter (
            name:
            let
              e = dirEntries.${name};
            in
            e == "directory"
            && pkgs.lib.hasPrefix "task_" name
            && builtins.pathExists (root + "/${name}/CMakeLists.txt")
          ) (builtins.attrNames dirEntries);

          mkTask =
            name:
            clangStdenv.mkDerivation rec {
              pname = name;
              version = "1.0";
              src = root + "/${name}";

              nativeBuildInputs = [
                pkgs.cmake
                pkgs.ninja
                pkgs.pkg-config
              ];
              buildInputs = [ ];

              cmakeFlags = [
                "-G"
                "Ninja"
                "-DCMAKE_BUILD_TYPE=Release"
                "-DCMAKE_CXX_STANDARD=23" # force fresh standard
                "-DCMAKE_CXX_EXTENSIONS=OFF"
              ];

              strictDeps = true;
              enableParallelBuilding = true;

              meta = with pkgs.lib; {
                description = "Build for ${name} using clang stdenv and CMake";
                license = licenses.mit;
                platforms = platforms.all;
              };
            };

          taskPkgs = builtins.listToAttrs (
            map (n: {
              name = n;
              value = mkTask n;
            }) taskDirs
          );

          allTasks = pkgs.symlinkJoin {
            name = "all-tasks";
            paths = builtins.attrValues taskPkgs;
          };
        in
        taskPkgs
        // {
          default = allTasks;
          all = allTasks;
        }
      );

      devShells = forAllSystems (
        system:
        let
          pkgs = import nixpkgs { inherit system; };
        in
        {
          default = pkgs.mkShell {
            packages = [
              pkgs.llvmPackages_21.clang
              pkgs.llvmPackages_21.lld
              pkgs.llvmPackages_21.libcxx
              pkgs.cmake
              pkgs.ninja
              pkgs.pkg-config
              pkgs.gdb
            ]
            ++ pkgs.lib.optionals pkgs.stdenv.isLinux [ pkgs.valgrind ];
          };
        }
      );

      checks = forAllSystems (
        system:
        let
          pkgs = import nixpkgs { inherit system; };
          root = ./.;
          dirEntries = builtins.readDir root;
          taskDirs = pkgs.lib.filter (
            name:
            let
              e = dirEntries.${name};
            in
            e == "directory"
            && pkgs.lib.hasPrefix "task_" name
            && builtins.pathExists (root + "/${name}/CMakeLists.txt")
          ) (builtins.attrNames dirEntries);
        in
        nixpkgs.lib.genAttrs taskDirs (n: self.packages.${system}.${n})
      );

      formatter = forAllSystems (
        system:
        let
          pkgs = import nixpkgs { inherit system; };
        in
        pkgs.nixpkgs-fmt
      );
    };
}
