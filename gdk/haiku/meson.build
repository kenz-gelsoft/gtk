
add_languages(['objc'])

gdk_haiku_sources = files(
#  'GdkHaikuView.c',
#  'GdkHaikuNSWindow.c',
  'gdkcursor-haiku.c',
  'gdkdevice-core-haiku.c',
  'gdkdevicemanager-core-haiku.c',
  'gdkdisplay-haiku.c',
  'gdkdisplaylinksource.c',
  'gdkdisplaymanager-haiku.c',
  'gdkdnd-haiku.c',
  'gdkevents-haiku.c',
  'gdkeventloop-haiku.c',
  'gdkglcontext-haiku.c',
  'gdkglobals-haiku.c',
  'gdkkeys-haiku.c',
  'gdkmonitor-haiku.c',
  'gdkproperty-haiku.c',
  'gdkscreen-haiku.c',
  'gdkselection-haiku.c',
  'gdktestutils-haiku.c',
  'gdkutils-haiku.c',
  'gdkvisual-haiku.c',
  'gdkwindow-haiku.c',
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

libgdk_haiku = static_library('gdk-haiku',
  gdk_haiku_sources, gdkconfig, gdkenum_h,
  include_directories: [confinc, gdkinc],
  c_args: ['-DGDK_COMPILATION', '-DG_LOG_DOMAIN="Gdk"', '-xobjective-c'],
  dependencies: [gdk_deps, gdk_haiku_deps])
