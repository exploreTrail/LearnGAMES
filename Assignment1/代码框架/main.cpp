#include "Triangle.hpp"
#include "kbhit.cpp"
#include "rasterizer.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos) {
  Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

  Eigen::Matrix4f translate;
  translate << 1, 0, 0, -eye_pos[0], 0, 1, 0, -eye_pos[1], 0, 0, 1, -eye_pos[2],
      0, 0, 0, 1;

  view = translate * view;

  return view;
}

Eigen::Matrix4f toMatrix4f(Eigen::Matrix3f m) {
  Eigen::Matrix4f tRet = Eigen::Matrix4f::Zero();
  tRet.block<3, 3>(0, 0) = m;
  tRet.row(3) = Vector4f{0, 0, 0, 1};
  return tRet;
}

Eigen::Matrix4f get_rotation(Vector3f axis, float angle) {
  float a = angle * MY_PI / 180.0;
  float cosa = cosf(a), sina = sinf(a);
  Eigen::Matrix3f I = Eigen::Matrix3f::Identity();
  axis = axis.normalized();
  Eigen::Matrix3f nhat;
  nhat << 0, -axis.z(), axis.y(), axis.z(), 0, -axis.x(), -axis.y(), axis.x(),
      0;
  return toMatrix4f(I + (nhat * nhat) * (1 - cosa) + sina * nhat);
}

Eigen::Matrix4f get_model_matrix(float rotation_angle) {
  Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

  // TODO: Implement this function
  // Create the model matrix for rotating the triangle around the Z axis.
  // Then return it.
  Vector3f axis{1, 1, 1};
  Eigen::Matrix4f t;
  t << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1;
  model = get_rotation(axis, rotation_angle);

  return model * t;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar) {
  // Students will implement this function

  Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();

  // TODO: Implement this function
  // Create the projection matrix for the given parameters.
  // Then return it.
  float fovY = eye_fov * MY_PI / 180.0;
  float cota = 1.f / tanf(fovY / 2);
  float zD = zNear - zFar;

  projection << -cota / aspect_ratio, 0, 0, 0, 0, -cota, 0, 0, 0, 0,
      (zNear + zFar) / zD, -2 * zNear * zFar / zD, 0, 0, 1, 0;

  return projection;
}

int main(int argc, const char **argv) {
  float angle = 0;
  bool command_line = false;
  std::string filename = "output.png";

  if (argc >= 3) {
    command_line = true;
    angle = std::stof(argv[2]); // -r by default
    if (argc == 4) {
      filename = std::string(argv[3]);
    } else
      return 0;
  }

  rst::rasterizer r(700, 700);

  Eigen::Vector3f eye_pos = {0, 0, 5};

  std::vector<Eigen::Vector3f> pos{{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};

  std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

  auto pos_id = r.load_positions(pos);
  auto ind_id = r.load_indices(ind);

  int key = 0;
  int frame_count = 0;

  if (command_line) {
    r.clear(rst::Buffers::Color | rst::Buffers::Depth);

    r.set_model(get_model_matrix(angle));
    r.set_view(get_view_matrix(eye_pos));
    r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

    r.draw(pos_id, ind_id, rst::Primitive::Triangle);
    cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
    image.convertTo(image, CV_8UC3, 1.0f);

    cv::imwrite(filename, image);

    return 0;
  }

  while (key != 27) {
    r.clear(rst::Buffers::Color | rst::Buffers::Depth);

    r.set_model(get_model_matrix(angle));
    r.set_view(get_view_matrix(eye_pos));
    r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

    r.draw(pos_id, ind_id, rst::Primitive::Triangle);

    cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
    image.convertTo(image, CV_8UC3, 1.0f);
    cv::imshow("image", image);
    key = cv::waitKey(10);

    std::cout << "frame count: " << frame_count++ << '\n';

    if (key == 'a') {
      angle += 10;
    } else if (key == 'd') {
      angle -= 10;
    }
    //  AD旋转
    // if (kbhit()) {
    //   char action = getchar();
    //   if (action == 'A')
    //     angle += 3;
    //   else if (action == 'D')
    //     angle -= 3;
    // }
  }

  return 0;
}
