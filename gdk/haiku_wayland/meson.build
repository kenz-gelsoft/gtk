gdk_haiku_sources = files(
  'gdkapplaunchcontext-haiku.c',
  'gdkcursor-haiku.c',
  'gdkdevice-haiku.c',
  'gdkdisplay-haiku.c',
  'gdkdnd-haiku.c',
  'gdkeventsource.c',
  'gdkkeys-haiku.c',
  'gdkglcontext-haiku.c',
  'gdkmonitor-haiku.c',
  'gdkscreen-haiku.c',
  'gdkselection-haiku.c',
  'gdkwindow-haiku.c',
  'wm-button-layout-translation.c',
)

gdk_haiku_public_headers = files(
  'gdkhaikudevice.h',
  'gdkhaikudisplay.h',
  'gdkhaikuglcontext.h',
  'gdkhaikumonitor.h',
  'gdkhaikuselection.h',
  'gdkhaikuwindow.h',
)

install_headers(gdk_haiku_public_headers, subdir: 'gtk-3.0/gdk/haiku')
install_headers('gdkhaiku.h', subdir: 'gtk-3.0/gdk')

gdk_haiku_deps = [
  shmlib,
  xkbdep,
  wlclientdep,
  wlprotocolsdep,
  wlcursordep,
  wlegldep,
]

# haiku protocols
wlprotocolsdep = dependency('haiku-protocols')
proto_dir = wlprotocolsdep.get_variable(pkgconfig: 'pkgdatadir')
assert(proto_dir != '', 'Could not get pkgdatadir from haiku-protocols.pc')

haiku_scanner = find_program('haiku-scanner')

# Format:
#  - protocol name
#  - protocol stability ('private', 'stable' or 'unstable')
#  - protocol version (if stability is 'unstable')
proto_sources = [
  ['gtk-shell', 'private', ],
  ['gtk-primary-selection', 'private', ],
  ['pointer-gestures', 'unstable', 'v1', ],
  ['xdg-shell', 'unstable', 'v6', ],
  ['xdg-shell', 'stable', ],
  ['xdg-foreign', 'unstable', 'v1', ],
  ['xdg-foreign', 'unstable', 'v2', ],
  ['tablet', 'unstable', 'v2', ],
  ['keyboard-shortcuts-inhibit', 'unstable', 'v1', ],
  ['server-decoration', 'private' ],
  ['xdg-output', 'unstable', 'v1', ],
  ['primary-selection', 'unstable', 'v1', ],
  ['cursor-shape-v1', 'private', ],
]
if wlprotocolsdep.version().version_compare('>=1.21')
  proto_sources += [['xdg-activation', 'staging', 'v1', ]]
endif

gdk_haiku_gen_headers = []

foreach p: proto_sources
  proto_name = p.get(0)
  proto_stability = p.get(1)

  if proto_stability == 'stable'
    output_base = proto_name
    input = join_paths(proto_dir, '@0@/@1@/@2@.xml'.format(proto_stability, proto_name, output_base))
  elif proto_stability == 'staging'
    proto_version = p.get(2)
    output_base = '@0@-@1@'.format(proto_name, proto_version)
    input = join_paths(proto_dir, '@0@/@1@/@2@.xml'.format(proto_stability, proto_name, output_base))
  elif proto_stability == 'private'
    output_base = proto_name
    input = 'protocol/@0@.xml'.format(proto_name)
  else
    proto_version = p.get(2)
    output_base = '@0@-@1@-@2@'.format(proto_name, proto_stability, proto_version)
    input = join_paths(proto_dir, '@0@/@1@/@2@.xml'.format(proto_stability, proto_name, output_base))
  endif

  gdk_haiku_gen_headers += custom_target('@0@ client header'.format(output_base),
                                           input: input,
                                           output: '@0@-client-protocol.h'.format(output_base),
                                           command: [
                                             haiku_scanner,
                                             'client-header',
                                             '@INPUT@', '@OUTPUT@',
                                           ])

  gdk_haiku_sources += custom_target('@0@ source'.format(output_base),
                                       input: input,
                                       output: '@0@-protocol.c'.format(output_base),
                                       command: [
                                         haiku_scanner,
                                         'private-code',
                                         '@INPUT@', '@OUTPUT@',
                                       ])
endforeach

libgdk_haiku = static_library('gdk-haiku',
                                gdk_haiku_sources, gdk_haiku_gen_headers, gdkconfig, gdkenum_h,
                                include_directories: [ confinc, gdkinc, ],
                                c_args: [
                                  '-DGDK_COMPILATION',
                                  '-DG_LOG_DOMAIN="Gdk"',
                                ] + common_cflags,
                                link_args: common_ldflags,
                                dependencies: [ gdk_deps, gdk_haiku_deps, ])
