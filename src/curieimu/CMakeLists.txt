if (MRAA_FIRMATA_FOUND)
  set (libname "curieimu")
  set (libdescription "Curie IMU Sensor using Firmata")
  set (module_src ${libname}.cpp)
  set (module_hpp ${libname}.hpp)
  upm_module_init(mraa ${CMAKE_THREAD_LIBS_INIT})
endif ()
