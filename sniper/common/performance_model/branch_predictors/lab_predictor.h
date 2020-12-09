#ifndef LAB_PREDICTOR_H
#define LAB_PREDICTOR_H

#include "branch_predictor.h"

#include <vector>

class NNBranchPredictor : public BranchPredictor
{
public:
   NNBranchPredictor(String name, core_id_t core_id);
   ~NNBranchPredictor();

   bool predict(IntPtr ip, IntPtr target); 
   void update(bool predicted, bool actual, IntPtr ip, IntPtr target);
private:

   void update_path(bool taken, IntPtr ip, IntPtr target);
   UInt32 bias_hash(IntPtr ip) const; 
   UInt32 index_entries(IntPtr ip, UInt32 i) const; 


   struct PathInfo {
      bool taken;
      IntPtr target;
      PathInfo(bool bt, IntPtr it): taken(bt), target(it) {}
   };

   SInt32 last_sum;
   UInt32 last_bias_index;
   std::vector<UInt32> last_indexes;
   std::vector<PathInfo> last_path;
   UInt32 last_path_index;  


   std::vector<PathInfo> path;
   UInt32 path_index; 

   UInt32 path_length; 
   UInt32 num_entries; 
   UInt32 num_bias_entries; 
   UInt32 weight_bits; 
   std::vector<std::vector<SInt32> > weights; 
   std::vector<SInt32> bias_weights; 
   UInt32 theta;
   SInt64  tc;
   UInt32 block_size;

   std::vector<double> coefficients; 
   double bias_coefficient;
};

#endif