project('game', 'c',
  version: '0.1',
  default_options: ['warning_level=2', 'c_std=c99'])

# Definir src e incluir directorios
src_dir = 'src'
include_dir = 'include'

# Enlistar todos los source files
sources = [
  'src/game.c',
  'src/main.c',
  'src/menu.c',
  'src/submenu.c',
  'src/matches.c',
  'src/puntuacion.c',
]

# Crear el ejecutable
executable('game', sources,
  include_directories: include_directories(include_dir),
  dependencies: dependency('ncurses'))