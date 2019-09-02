CXX = g++
BUILDARGS = -g -std=c++14
LDLIBS = -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_aruco -lopencv_bgsegm -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dpm -lopencv_face -lopencv_photo -lopencv_fuzzy -lopencv_hdf -lopencv_hfs -lopencv_img_hash -lopencv_line_descriptor -lopencv_optflow -lopencv_ovis -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_sfm -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_dnn -lopencv_plot -lopencv_xfeatures2d -lopencv_shape -lopencv_video -lopencv_ml -lopencv_ximgproc -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_flann -lopencv_xobjdetect -lopencv_imgcodecs -lopencv_objdetect -lopencv_xphoto -lopencv_imgproc -lopencv_core

tests: tests.cpp image_categorizer.o image_manipulator.o
	$(CXX) $(BUILDARGS) -o tests tests.cpp image_categorizer.o image_manipulator.o $(LDLIBS)

image_categorizer.o: image_manipulator.o
	$(CXX) $(BUILDARGS) -c -o image_categorizer.o ../src/image_categorizer.cpp image_manipulator.o $(LDLIBS)

image_manipulator.o:
	$(CXX) $(BUILDARGS) -c -o image_manipulator.o ../src/image_manipulator.cpp $(LDLIBS)
