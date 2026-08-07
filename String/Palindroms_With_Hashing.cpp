// 1. تعريف الهاشينج وتفعيل الـ suffix
Hashing hash(s, true); 
int n = s.size();

// متجهات لتخزين أطوال أكبر باليندروم عند كل مركز
vector<int> odd_len(n);  // للباليندروم الفردي
vector<int> even_len(n); // للباليندروم الزوجي

// ==========================================
// أولاً: الباليندروم الفردي (Odd Palindromes)
// المركز بيكون عند الحرف i نفسه
// ==========================================
for (int i = 0; i < n; i++) {
    // أقل نصف قطر هو 0 (الحرف نفسه)، وأكبر نصف قطر يحده أطراف الـ string
    int low = 0, high = min(i, n - 1 - i), best_radius = 0;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        // لو الجزء من (i - mid) إلى (i + mid) باليندروم
        if (hash.is_pal(i - mid, i + mid)) {
            best_radius = mid; // نحفظ الإجابة
            low = mid + 1;     // ونحاول نكبر نصف القطر
        } else {
            high = mid - 1;    // نصف القطر كبير جداً، نصغره
        }
    }
    // الطول الكلي للباليندروم الفردي
    odd_len[i] = (2 * best_radius) + 1;
}

// ==========================================
// ثانياً: الباليندروم الزوجي (Even Palindromes)
// المركز بيكون بين الحرف i والحرف i+1
// ==========================================
for (int i = 0; i < n - 1; i++) {
    // أقل نصف قطر ممكن هو 1 (يعني حرفين i و i+1)
    int low = 1, high = min(i + 1, n - 1 - i), best_radius = 0;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        // البداية هتكون i - mid + 1، والنهاية i + mid
        if (hash.is_pal(i - mid + 1, i + mid)) {
            best_radius = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    // الطول الكلي للباليندروم الزوجي
    even_len[i] = 2 * best_radius;
}
