#pragma once
#include <string>

constexpr int MAXBIT = 10;
constexpr int MAXVALUE = 10000;
constexpr int MAXLEAF = 10;
constexpr int MAXNODE = MAXLEAF * 2 - 1;

using namespace std;

struct HCodeType {
  //  string bit;
  int bit[MAXLEAF];
  int start;
}; /* ����ṹ�� */

struct HNodeType {
  int weight, parent, lChild, rChild;
  char value;
}; /* ���ṹ�� */

class HuffmanTree {
  HNodeType HuffNode[MAXNODE];
  HCodeType HuffCode[MAXLEAF];

  int n = 10;  // �ֵ��С

  void init() {
    for (int i = 0; i < MAXNODE; i++) {
      HuffNode[i].weight = 0;  //Ȩֵ
      HuffNode[i].parent = -1;
      HuffNode[i].lChild = -1;
      HuffNode[i].rChild = -1;
      HuffNode[i].value = '@';  //ʵ��ֵ���ɸ�������滻Ϊ��ĸ
    }
  }

 public:
  string Dict[MAXLEAF];
  string txtBuf, sendBuf;

  HuffmanTree() { init(); }

  void importStr(const string& str) {  // ͨ���ַ���������������
    init();
    txtBuf = str;
    int i, j, m1, m2, x1, x2;
    // ����ͳ�����ֳ��ֵĴ���
    int charCnt[10]{0};
    for (auto ch : str) {
      charCnt[ch - '0']++;
    }
    for (int i = 0; i < 10; i++) {
      HuffNode[i].value = i + '0';
      HuffNode[i].weight = charCnt[i];
    }
    for (i = 0; i < n - 1; i++) {
      m1 = m2 = MAXVALUE; /* m1��m2�д�������޸�����ҽ��Ȩֵ��С��������� */
      x1 = x2 = 0;
      /* �ҳ����н����Ȩֵ��С���޸�����������㣬���ϲ�֮Ϊһ�Ŷ����� */
      for (j = 0; j < n + i; j++) {
        if (HuffNode[j].weight < m1 && HuffNode[j].parent == -1) {
          m2 = m1;
          x2 = x1;
          m1 = HuffNode[j].weight;
          x1 = j;
        } else if (HuffNode[j].weight < m2 && HuffNode[j].parent == -1) {
          m2 = HuffNode[j].weight;
          x2 = j;
        }
      } /* end for */
      /* �����ҵ��������ӽ�� x1��x2 �ĸ������Ϣ */
      HuffNode[x1].parent = n + i;
      HuffNode[x2].parent = n + i;
      HuffNode[n + i].weight = HuffNode[x1].weight + HuffNode[x2].weight;
      HuffNode[n + i].lChild = x1;
      HuffNode[n + i].rChild = x2;
    }
    calcDict();  // �����ֵ�
  }

  void calcDict() {  //�����ֵ�
    string ret;
    HCodeType cd;
    int i, j, c, p;
    for (i = 0; i < n; i++) {
      cd.start = n - 1;
      c = i;
      p = HuffNode[c].parent;
      while (p != -1) /* �������� */
      {
        if (HuffNode[p].lChild == c)
          cd.bit[cd.start] = 0;
        else
          cd.bit[cd.start] = 1;
        cd.start--; /* �����ĵ�һλ */
        c = p;
        p = HuffNode[c].parent; /* ������һѭ������ */
      }                         /* end while */

      /* ���������ÿ��Ҷ���Ĺ���������ͱ������ʼλ */
      for (j = cd.start + 1; j < n; j++) {
        HuffCode[i].bit[j] = cd.bit[j];
      }
      HuffCode[i].start = cd.start;
    } /* end for */
    for (int i = 0; i < 10; i++) {
      string buf;
      for (int j = HuffCode[i].start + 1; j < 10; j++)
        buf.push_back((HuffCode[i].bit[j]) + '0');
      //      qDebug() << buf;
      Dict[i] = buf;
    }
  }

  string getSendBuf() {
    sendBuf.clear();
    for (auto ch : txtBuf) {
      sendBuf.append(Dict[ch - '0']);
    }
    //    qDebug() << "sendBuf = " << sendBuf;
    return sendBuf;
  }

  // string getMat() {  // ���ؾ����ַ��������ڽ��ն˽���
  //   string ret;
  //   for (int i = 0; i < MAXNODE; i++) {
  //     string buf;
  //     buf.append(string("%1").arg(HuffNode[i].weight, 5, 10,
  //     QLatin1Char('0'))); if (HuffNode[i].parent == -1)
  //       buf.append("99");
  //     else
  //       buf.append(
  //           string("%1").arg(HuffNode[i].parent, 2, 10, QLatin1Char('0')));

  //    if (HuffNode[i].lChild == -1)
  //      buf.append("99");
  //    else
  //      buf.append(
  //          string("%1").arg(HuffNode[i].lChild, 2, 10, QLatin1Char('0')));
  //    if (HuffNode[i].rChild == -1)
  //      buf.append("99");
  //    else
  //      buf.append(
  //          string("%1").arg(HuffNode[i].rChild, 2, 10, QLatin1Char('0')));

  //    buf.append(to_string(HuffNode[i].value));
  //    ret.append(buf);
  //  }
  //  return ret;
  //}

  void importMat(const string& mat) {  // �����յ��ľ����ַ��������ڽ���
                                       //    qDebug() << "importMat ing!";
    for (int i = 0; i < MAXNODE; i++) {
      int s = i * 12;
      string temp;
      temp = mat.substr(s + 0, 5);  // 0-4
      HuffNode[i].weight = atoi(temp.c_str());
      temp = mat.substr(s + 5, 2);  // 5-6
      if (temp != "99")
        HuffNode[i].parent = atoi(temp.c_str());
      else
        HuffNode[i].parent = -1;
      temp = mat.substr(s + 7, 2);  // 7-8
      if (temp != "99")
        HuffNode[i].lChild = atoi(temp.c_str());
      else
        HuffNode[i].lChild = -1;
      temp = mat.substr(s + 9, 2);  // 9-10
      if (temp != "99")
        HuffNode[i].rChild = atoi(temp.c_str());
      else
        HuffNode[i].rChild = -1;

      HuffNode[i].value = mat[s + 11];
    }
  }

  string decoding(const string& str) {  // ������Ķ������ַ������룬���ؽ��
    string ret;
    int i, tmp = 0;
    //    char num[16384];
    char* num = new char[str.size() + 10]{0};
    for (i = 0; i < str.size(); i++) {
      if (str[i] == '0')
        num[i] = 0;
      else
        num[i] = 1;
    }
    i = 0;
    while (i < str.size()) {
      tmp = MAXNODE - 1;
      while ((HuffNode[tmp].lChild != -1) && (HuffNode[tmp].rChild != -1)) {
        if (num[i] == 0) {
          tmp = HuffNode[tmp].lChild;
        } else
          tmp = HuffNode[tmp].rChild;
        i++;
      }
      //      printf("%c", HuffNode[tmp].value);
      ret.append(to_string(HuffNode[tmp].value));
    }
    //    qDebug() << ret;
    delete[] num;
    return ret;
  }
};
