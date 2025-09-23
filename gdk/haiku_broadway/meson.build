gdk_haiku_sources = files(
  'gdkcursor-haiku.c',
  'gdkdevice-haiku.c',
  'gdkdevicemanager-haiku.c',
  'gdkdisplay-haiku.c',
  'gdkdnd-haiku.c',
  'gdkeventsource.c',
  'gdkglobals-haiku.c',
  'gdkkeys-haiku.c',
  'gdkmonitor-haiku.c',
  'gdkproperty-haiku.c',
  'gdkscreen-haiku.c',
  'gdkselection-haiku.c',
  'gdktestutils-haiku.c',
  'gdkvisual-haiku.c',
  'gdkwindow-haiku.c',
  'gdkhaiku-server.c',
)

gdk_haiku_public_headers = files(
  'gdkhaikudisplay.h',
  'gdkhaikuwindow.h',
  'gdkhaikucursor.h',
  'gdkhaikumonitor.h',
  'gdkhaikuvisual.h',
)

install_headers(gdk_haiku_public_headers, subdir: 'gtk-3.0/gdk/haiku/')
install_headers('gdkhaiku.h', subdir: 'gtk-3.0/gdk/')

gdk_haiku_deps = [shmlib]

gen_c_array = find_program('gen-c-array.py')

clienthtml_h = custom_target('clienthtml.h',
  input : 'client.html',
  output : 'clienthtml.h',
  command : [
    gen_c_array,
    '--array-name=client_html',
    '--output=@OUTPUT@',
    '@INPUT@',
  ],
)

haikujs_h = custom_target('haikujs.h',
  input : ['haiku.js', 'rawinflate.min.js'],
  output : 'haikujs.h',
  command : [
    gen_c_array,
    '--array-name=haiku_js',
    '--output=@OUTPUT@',
    '@INPUT0@','@INPUT1@',
  ],
)

libgdk_haiku = static_library('gdk-haiku',
  clienthtml_h, haikujs_h,
  gdk_haiku_sources, gdkconfig, gdkenum_h,
  include_directories: [confinc, gdkinc],
  c_args: [
    '-DGDK_COMPILATION',
    '-DG_LOG_DOMAIN="Gdk"',
  ] + common_cflags,
  link_args: common_ldflags,
  dependencies: [gdk_deps, gdk_haiku_deps])

# gtk4-haikud

haikud_syslib = os_win32 ? cc.find_library('ws2_32') : shmlib

executable('haikud',
  clienthtml_h, haikujs_h,
  'haikud.c', 'haiku-server.c', 'haiku-buffer.c', 'haiku-output.c',
  include_directories: [confinc, gdkinc, include_directories('.')],
  c_args: ['-DGDK_COMPILATION', '-DG_LOG_DOMAIN="Gdk"', ],
  dependencies : [haikud_syslib, gdk_deps],
  install : true)
