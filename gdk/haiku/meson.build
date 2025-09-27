
add_languages(['cpp'])

gdk_haiku_sources = files(
  'GdkHaikuView.cpp',
  'GdkHaikuBWindow.cpp',
  'gdkcursor-haiku.cpp',
  'gdkdevice-core-haiku.cpp',
  'gdkdevicemanager-core-haiku.cpp',
  'gdkdisplay-haiku.cpp',
  'gdkdisplaymanager-haiku.cpp',
  'gdkdnd-haiku.cpp',
  'gdkevents-haiku.cpp',
  'gdkeventloop-haiku.cpp',
  'gdkeventsource.cpp',
  'gdkglcontext-haiku.cpp',
  'gdkglobals-haiku.cpp',
  'gdkkeys-haiku.cpp',
  'gdkmonitor-haiku.cpp',
  'gdkproperty-haiku.cpp',
  'gdkscreen-haiku.cpp',
  'gdkselection-haiku.cpp',
  'gdktestutils-haiku.cpp',
  'gdkutils-haiku.cpp',
  'gdkvisual-haiku.cpp',
  'gdkwindow-haiku.cpp',
)

gdk_haiku_public_headers = files(
  'gdkhaiku-cocoa-access.h',
  'gdkhaikucursor.h',
  'gdkhaikudevice-core.h',
  'gdkhaikudevicemanager-core.h',
  'gdkhaikudisplay.h',
  'gdkhaikudisplaymanager.h',
  'gdkhaikudnd.h',
  'gdkhaikukeys.h',
  'gdkhaikumonitor.h',
  'gdkhaikuscreen.h',
  'gdkhaikuutils.h',
  'gdkhaikuvisual.h',
  'gdkhaikuwindow.h',
)

install_headers(gdk_haiku_public_headers, subdir: 'gtk-3.0/gdk/haiku')
install_headers('gdkhaiku.h', subdir: 'gtk-3.0/gdk')

#core_graphics_dep = dependency('appleframeworks', modules : 'CoreGraphics', required : true)
#appkit_dep = dependency('appleframeworks', modules : 'AppKit', required : true)
#cocoa_dep = dependency('appleframeworks', modules : 'Cocoa', required : true)
#carbon_dep = dependency('appleframeworks', modules : 'Carbon', required : true)
#haiku_dep = dependency('appleframeworks', modules : 'QuartzCore', required : true)
#iosurface_dep = dependency('appleframeworks', modules: 'IOSurface', required: true)

#gdk_haiku_deps = [ core_graphics_dep, appkit_dep, cocoa_dep, carbon_dep, haiku_dep, iosurface_dep ]
gdk_haiku_deps = []

common_args = ['-DGDK_COMPILATION', '-DG_LOG_DOMAIN="Gdk"']

libgdk_haiku = static_library('gdk-haiku',
  gdk_haiku_sources, gdkconfig, gdkenum_h,
  include_directories: [confinc, gdkinc],
  c_args: common_args,
  cpp_args: common_args,
  dependencies: [gdk_deps, gdk_haiku_deps])
