#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <climits>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// ============================================================================
// 用户当前提交的代码 (包含两处关键缺陷供断点调试)
// ============================================================================
class SolutionUser {
public:
    int getMinimumDifference(TreeNode* root) {
        // ⚠️ 致命 Bug 1: 
        // 在 C++ 中，^ 是按位异或 (XOR) 运算符，不是幂运算符！
        // 10 ^ 6 对应的二进制计算：(1010)_2 ^ (0110)_2 = (1100)_2 = 12！
        // 因此 min 初始值不是 1,000,000，而是 12！
        int min = 10^6;

        std::cout << "  [调试栈帧] 访问节点 val = " << root->val 
                  << " | 当前初始 min (10^6) = " << min << std::endl;

        if (root->left == nullptr && root->right == nullptr) {
            return min;
        }

        // ⚠️ 算法逻辑缺陷 2:
        // 二叉搜索树的最小差值不一定发生在「直接父子节点」之间！
        // 比如根节点的最接近较小值，其实是左子树的最右下节点（中序遍历前驱），而非直接左孩子。
        if (root->left != nullptr) {
            int leftDiff = root->val - root->left->val;
            std::cout << "  [调试计算] 左子节点差值: " << root->val << " - " 
                      << root->left->val << " = " << leftDiff << std::endl;
            min = std::min(leftDiff, min);
            std::cout << "  [调试结果] std::min(" << leftDiff << ", 12) 导致 min 变成了: " << min << std::endl;
            
            int leftSubMin = getMinimumDifference(root->left);
            min = std::min(min, leftSubMin);
        }

        if (root->right != nullptr) {
            int rightDiff = root->right->val - root->val;
            min = std::min(rightDiff, min);
            int rightSubMin = getMinimumDifference(root->right);
            min = std::min(min, rightSubMin);
        }

        return min;
    }
};

// ============================================================================
// 正确最优解法：利用 BST 中序遍历升序特性的双指针法
// ============================================================================
class SolutionOptimal {
private:
    int minDiff = INT_MAX;
    TreeNode* prev = nullptr;

    void inOrder(TreeNode* root) {
        if (!root) return;
        inOrder(root->left);
        if (prev != nullptr) {
            minDiff = std::min(minDiff, root->val - prev->val);
        }
        prev = root;
        inOrder(root->right);
    }

public:
    int getMinimumDifference(TreeNode* root) {
        minDiff = INT_MAX;
        prev = nullptr;
        inOrder(root);
        return minDiff;
    }
};

// ============================================================================
// 调试入口
// ============================================================================
int main() {
    std::cout << "============================================================" << std::endl;
    std::cout << "🧪 正在调试测试用例: [100000, 0] (根节点 100000，左子节点 0)" << std::endl;
    std::cout << "============================================================" << std::endl;

    // 手动构造二叉树:
    //      100000
    //      /
    //     0
    TreeNode* root = new TreeNode(100000);
    root->left = new TreeNode(0);

    // 1. 运行用户当前代码 (在此处断点即可跟入 getMinimumDifference)
    SolutionUser userSolution;
    std::cout << "\n>>> 开始执行当前用户代码: <<<" << std::endl;
    int userResult = userSolution.getMinimumDifference(root);
    std::cout << "\n❌ 用户代码返回结果: " << userResult << " (预期正确值: 100000)" << std::endl;

    // 2. 运行标准最优解对比
    SolutionOptimal optimalSolution;
    int optimalResult = optimalSolution.getMinimumDifference(root);
    std::cout << "✅ 标准最优解返回结果: " << optimalResult << std::endl;

    // 3. 补充测试用例 2: 揭示「只比直接父子节点」的隐蔽错误
    // 树结构: [236, 104, 701, null, 227, null, 911]
    // 最小差值为 236 与 227 之间: |236 - 227| = 9
    std::cout << "\n============================================================" << std::endl;
    std::cout << "🧪 补充测试用例 2: [236, 104, 701, null, 227, null, 911]" << std::endl;
    std::cout << "   (227 是 104 的右子树，与 236 差值仅为 9，但并非直接父子！)" << std::endl;
    std::cout << "============================================================" << std::endl;
    TreeNode* root2 = new TreeNode(236);
    root2->left = new TreeNode(104);
    root2->right = new TreeNode(701);
    root2->left->right = new TreeNode(227);
    root2->right->right = new TreeNode(911);

    int userResult2 = userSolution.getMinimumDifference(root2);
    int optimalResult2 = optimalSolution.getMinimumDifference(root2);
    std::cout << "❌ 用户逻辑返回: " << userResult2 << " (误判，错失跨层前驱后继)" << std::endl;
    std::cout << "✅ 标准中序遍历返回: " << optimalResult2 << " (准确找到 |236 - 227| = 9)" << std::endl;

    // 清理内存
    delete root->left;
    delete root;
    delete root2->left->right;
    delete root2->left;
    delete root2->right->right;
    delete root2->right;
    delete root2;

    return 0;
}
