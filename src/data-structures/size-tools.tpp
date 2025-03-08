#ifndef __MINI_TOOLS__UTILS__SIZE_TOOLS_CPP__
#define __MINI_TOOLS__UTILS__SIZE_TOOLS_CPP__

namespace mini_tools {
namespace data_structures {

  template <typename T>
  VEC_SZ SizeTools<T>::generateSizes(CR_VEC2<T> vecs) {
    VEC_SZ sizes;
    for (CR_VEC<T> v : vecs) {
      sizes.push_back(v.size());
    }
    return sizes;
  }

  template <typename T>
  size_t SizeTools<T>::getMax(VEC_SZ &sizes) {
    size_t max = 0;

    for (CR_LLI sz : sizes) {
      if (sz > max) max = sz;
    }

    return max;
  }

  template <typename T>
  size_t SizeTools<T>::getMax(CR_VEC2<T> vecs) {
    VEC_SZ sizes = SizeTools<T>::generateSizes(vecs);
    return SizeTools<T>::getMax(sizes);
  }

  template <typename T>
  VEC_SZ SizeTools<T>::getDifferences(VEC_SZ &sizes) {

    VEC_SZ differences;
    size_t max = SizeTools<T>::getMax(sizes);

    for (CR_SZ sz : sizes) {
      differences.push_back(max - sz);
    }

    return differences;
  }

  template <typename T>
  VEC_LLI SizeTools<T>::getDifferences(
    VEC_SZ &sizes, CR_LLI targetSize
  ) {
    VEC_LLI differences;

    for (CR_SZ sz : sizes) {
      differences.push_back(targetSize - sz);
    }

    return differences;
  }

  template <typename T>
  VEC_SZ SizeTools<T>::getDifferences(CR_VEC2<T> vecs) {
    VEC_SZ sizes = SizeTools<T>::generateSizes(vecs);
    return SizeTools<T>::getDifferences(sizes);
  }

  template <typename T>
  VEC_LLI SizeTools<T>::getDifferences(
    CR_VEC2<T> vecs,
    CR_LLI targetSize
  ) {
    VEC_SZ sizes = SizeTools<T>::generateSizes(vecs);
    return SizeTools<T>::getDifferences(sizes, targetSize);
  }

  template <typename T>
  void SizeTools<T>::balance(
    CR_VEC_SZ differences,
    VEC2<T> &vecs,
    CR<T> coveringValue
  ) {
    for (int i = 0; i < vecs.size(); i++) {
      std::vector<T> additions(differences[i], coveringValue);
      vecs[i].reserve(vecs[i].size() + differences[i]);
      vecs[i].insert(vecs[i].end(), additions.begin(), additions.end());
    }
  }

  template <typename T>
  void SizeTools<T>::balance(
    CR_VEC_LLI differences,
    VEC2<T> &vecs,
    CR<T> coveringValue
  ) {
    for (int i = 0; i < vecs.size(); i++) {
      if (differences[i] < 0) {
        vecs[i] = std::vector<T>(
          vecs[i].begin(),
          vecs[i].end() + differences[i]
        );
      }
      else if (differences[i] > 0) {
        std::vector<T> additions(differences[i], coveringValue);
        vecs[i].reserve(vecs[i].size() + differences[i]);
        vecs[i].insert(vecs[i].end(), additions.begin(), additions.end());
      }
    }
  }

  template <typename T>
  void SizeTools<T>::balance(
    VEC2<T> &vecs,
    CR<T> coveringValue
  ) {
    SizeTools<T>::balance(
      SizeTools<T>::getDifferences(vecs),
      vecs, coveringValue
    );
  }

  template <typename T>
  void SizeTools<T>::balance(
    VEC2<T> &vecs,
    CR<T> coveringValue,
    LLI targetSize
  ) {
    if (targetSize < 0) targetSize = 0;

    SizeTools<T>::balance(
      SizeTools<T>::getDifferences(vecs, targetSize),
      vecs, coveringValue
    );
  }
}}

#endif // __MINI_TOOLS__UTILS__SIZE_TOOLS_CPP__