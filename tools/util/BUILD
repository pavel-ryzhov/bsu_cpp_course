cc_library(
    name = "util",
    hdrs = [
        "dist.h",
        "strict_iterator.h",
        "util.h",
    ],
    visibility = ["//visibility:public"],
)

# cc_library(
#     name = "c_img",
#     hdrs = [
#         "CImg.h",
#     ],
#     defines = ["cimg_use_png"],
#     visibility = ["//visibility:public"],
# )

cc_library(
    name = "image_tools",
    hdrs = [
        "image.h",
        "rgb.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@libpng",
    ],
)
