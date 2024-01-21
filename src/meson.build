statsadder_adw_sources = [
  'main.c',
  'statsadder_adw-window.c',
  'statsadder_adw-application.c',
]

statsadder_adw_deps = [
  dependency('libadwaita-1', version: '>= 1.0'),
]

gnome = import('gnome')

statsadder_adw_sources += gnome.compile_resources('statsadder_adw-resources',
  'statsadder_adw.gresource.xml',
  c_name: 'statsadder_adw'
)

executable('statsadder-adw', statsadder_adw_sources,
  dependencies: statsadder_adw_deps,
  install: true,
)
