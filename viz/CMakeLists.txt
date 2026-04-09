


rock_vizkit_plugin_qt5(ASN_Viz-viz-qt5
    ASNViz.cpp
    MOC ASNViz.hpp
        LaserScanViz.hpp
        RigidBodyStateViz.hpp
        PointcloudViz.hpp
        DepthMapViz.hpp
        TrajectoryViz.hpp
        MapViz.hpp
    SOURCES MapViz.cpp
    DEPS ASN_Viz
    DEPS_PKGCONFIG base-types base_support sensor_samples_support base-viz-qt5 asn1
    HEADERS ASNViz.hpp)
