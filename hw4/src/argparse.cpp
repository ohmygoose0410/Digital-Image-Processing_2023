#include <argparse/argparse.hpp>

int parse_arguments(
    const int argc,
    const char** argv,
    std::string* goldPath,
    std::string* srcPath,
    uint16_t* mSize,
    int16_t* mAngle,
    float* mK,
    uint16_t* gSize,
    float* gSigma,
    float* gK
) {
    argparse::ArgumentParser program;

    program.add_argument("-gp", "--goldenPath")
        .help("Input original image path")
        .default_value("");

    program.add_argument("blurPath")
		.help("Input blur image path");

	program.add_argument("motionKernelSize")
		.help("Motion kernel size")
		.scan<'i', int>();

	program.add_argument("motionKernelAngle")
		.help("Motion angle")
		.scan<'i', int>();

	program.add_argument("motionK")
		.help("Wiener filter K")
		.scan<'g', float>();

	program.add_argument("gaussianKernelSize")
		.help("Gaussian kernel size")
		.scan<'i', int>();

	program.add_argument("gaussianSigma")
		.help("Gaussian SD")
		.scan<'i', int>();
	
	program.add_argument("gaussianK")
		.help("Wiener filter K")
		.scan<'g', float>();

    try
	{
		program.parse_args(argc, argv);
	}
	catch (const std::exception &err)
	{
		std::cerr << err.what() << std::endl;
		std::cerr << program;
		return -1;
	}

    *goldPath   = program.get<std::string>("--goldenPath");
	*srcPath    = program.get<std::string>("blurPath");
	*mSize	    = program.get<int>("motionKernelSize");
	*mAngle	    = program.get<int>("motionKernelAngle");
	*mK		    = program.get<float>("motionK");
	*gSize	    = program.get<int>("gaussianKernelSize");
	*gSigma	    = program.get<int>("gaussianSigma");
	*gK		    = program.get<float>("gaussianK");

    return 1;
}