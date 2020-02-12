#ifndef CATEGORY_H
#define CATEGORY_H

#include <vector>

template <typename EntryClass>
class Category
{
public:
   int AddEntry(EntryClass* entry)
   {
      mEntries.push_back(entry);
      return (int)mEntries.size() - 1;
   }

   EntryClass& operator[](int index) { return *(mEntries[index]); }
   int Size() { return (int)mEntries.size(); }

private:
   std::vector<EntryClass*> mEntries;
};

#define DECLARE_CLOSED_CATEGORY(classname)                                    \
   public:                                                                    \
         classname(Category<classname>&);                                     \
         int GetCategoryIndex() const {return mCategoryIndex;}                \
         static Category<classname>& GetCategory() {return sCategory;}        \
         friend bool operator==(const classname& lhs, const classname& rhs)   \
         {                                                                    \
            return lhs.GetCategoryIndex() == rhs.GetCategoryIndex();          \
         }                                                                    \
         classname(classname const&) = delete;                                \
         void operator=(classname const&) = delete;                           \
   private:                                                                   \
      const int mCategoryIndex;                                               \
      static Category<classname> sCategory;

#define INITIALIZE_CLOSED_CATEGORY(classname) mCategoryIndex(sCategory.AddEntry(this))

#define DEFINE_CLOSED_CATEGORY(classname)                            \
   Category<classname> classname::sCategory = Category<classname>();

#endif