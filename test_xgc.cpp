#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "adios2.h"
#include "mgard_api.h"

int main(int argc, char **argv) {
  double tol, result;
  int out_size;
  unsigned char *compressed_data = 0;
#if 0
  MPI_Init(&argc, &argv);
  int rank, comm_size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm comm = MPI_COMM_SELF;

  if (argc != 3) {
    cerr << "Wrong arugments!\n";
    return 1;
  }
#endif
  adios2::ADIOS ad;
  adios2::IO reader_io = ad.DeclareIO("XGC");

  adios2::Engine reader = reader_io.Open("/gpfs/alpine/world-shared/csc143/jyc/summit/d3d_coarse_small/restart_dir/xgc.f0_debug.00702.10.bp", adios2::Mode::Read);
  // Inquire variable
  adios2::Variable<double> var_i_f_in;

  var_i_f_in = reader_io.InquireVariable<double>("i_f");

  std::vector<std::size_t> shape = var_i_f_in.Shape();;

  std::cout << shape[0] << " " << shape[1] << " "
            << shape[2] << " " << shape[3] << "\n";

  var_i_f_in.SetSelection(adios2::Box<adios2::Dims>(
                        {0, 0, 0, 0}, {shape[0],  shape[1], shape[2], shape[3]}));

  std::vector<double> i_f;
  reader.Get<double>(var_i_f_in, i_f);

  reader.Close();

//  const std::array<std::size_t, 1> dims = {u_global_size};
  const std::array<std::size_t, 4> dims = {shape[0], shape[1], shape[2], shape[3]};

  const mgard::TensorMeshHierarchy<4, double> hierarchy(dims);
  const size_t ndof = hierarchy.ndof();
  std::cout << "ndof = " << ndof << "\n";
  tol = 1e10;
  const mgard::CompressedDataset<4, double> compressed =
          mgard::compress(hierarchy, i_f.data(), 0.0, tol);

}
