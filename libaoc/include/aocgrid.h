#pragma once

#include <vector>
#include <string>
#include <deque>
#include <memory>
#include <array>
#include <iostream>
#include <algorithm>

typedef std::array<int, 2> Coord;

template <class T> using YData = std::deque<T>;
template <class T> using XPtr = YData<T>*;
template <class T> using XData = std::deque<std::unique_ptr<YData<T>>>;

template <class T> class Grid {
  public:
    Grid(): Grid(0) {}
    Grid(T defaultval): m_mx(0), m_my(0), m_px(-1), m_py(-1), m_defaultval(defaultval) {}

    Coord parseLine(const std::string &s) {
      // returns coords of last point parsed
      static int y = 0;
      Coord tmp = {-1, y++};
      for (auto c: s) {
        tmp[0]++;
        safeSet(tmp, c);
      }
      return tmp;
    }

    void printGrid() {
      T v;
      char c;
      for (int y = m_my; y <= m_py; y++) {
        for (int x = m_mx; x <= m_px; x++) {
          v = safeGet(x, y);
          std::cout << v;
        }
        std::cout << "\n";
      }
    }

    void debugGrid() {
      #ifdef AOCDEBUG
        printGrid();
      #endif
    }

    void clearMap() {
      for (int y = m_my; y <= m_py; y++) for (int x = m_mx; x <= m_px; x++)
        if (get(x, y) != m_defaultval) set(x, y, m_defaultval);
    }

    void getActualExtents(int &mx, int &px, int &my, int &py) {
      mx = m_mx;
      px = m_px;
      my = m_my;
      py = m_py;
    }

    int mx() {return m_mx;}
    int px() {return m_px;}
    int my() {return m_my;}
    int py() {return m_py;}

    T safeGet(int x, int y, T defaultval) {
      if (x > m_px || x < m_mx || y > m_py || y < m_my) return defaultval;
      return get(x, y);
    }

    T safeGet(Coord xy, T defaultval) {
      if (xy[0] > m_px || xy[0] < m_mx || xy[1] > m_py || xy[1] < m_my) return defaultval;
      return get(xy);
    }

    T safeGet(int x, int y) {return safeGet(x, y, m_defaultval);}
    T safeGet(Coord xy) {return safeGet(xy, m_defaultval);}

    void safeSet(int x, int y, T v) {
      checkExtents({x, y});
      set(x, y, v);
    }

    void safeSet(Coord xy, T v) {
      checkExtents(xy);
      set(xy, v);
    }

    Coord index2coord(int i) {
      int width = m_px - m_mx + 1;
      int x = i % width;
      return Coord({x, i/width});
    }

    int coord2index(Coord xy) {
      return xy2index(xy[0], xy[1]);
    }

    int xy2index(int x, int y) {
      return x + y*(m_px - m_mx + 1);
    }

    void insertColumn(int insert_before) {
      insertAndFillX(insert_before - m_mx);
      m_px++;
    }

    void insertRow(int insert_before) {
      insertY(insert_before - m_my);
      m_py++;
    }

  private:
    XData<T> m_grid;
    int m_mx, m_my, m_px, m_py;
    T m_defaultval;

    void addPX() {m_grid.push_back(std::make_unique<YData<T>>());}
    void insertX(int insert_before) {
      m_grid.insert(std::next(m_grid.begin(), insert_before), std::make_unique<YData<T>>());
    }
    void addMX() {m_grid.push_front(std::make_unique<YData<T>>());}

    void addPY() {for (auto &x: m_grid) addPY(x.get());}
    void addPY(XPtr<T> x) {
      x->push_back(m_defaultval);
    }

    void insertY(int insert_before) {for (auto &x: m_grid) insertY(insert_before, x.get());}
    void insertY(int insert_before, XPtr<T> x) {
      x->insert(std::next(x->begin(), insert_before), m_defaultval);
    }

    void addMY() {for (auto &x: m_grid) addMY(x.get());}
    void addMY(XPtr<T> x) {
      x->push_front(m_defaultval);
    }

    void addAndFillPX() {
      addPX();
      XPtr<T> pxp = m_grid.back().get();
      for (int i = m_py - m_my + 1; i > 0; i--) addPY(pxp);
    }

    void insertAndFillX(int insert_before) {
      insertX(insert_before);
      XPtr<T> pxp = std::next(m_grid.begin(), insert_before)->get();
      for (int i = m_py - m_my + 1; i > 0; i--) addPY(pxp);
    }

    void addAndFillMX() {
      addMX();
      XPtr<T> mxp = m_grid.front().get();
      for (int i = m_py - m_my + 1; i > 0; i--) addPY(mxp);
    }

    void set(const Coord c, T v) {
      set(c[0], c[1], v);
    }

    void set(int x, int y, T v) {
      m_grid[x - m_mx].get()->at(y - m_my) = v;
    }

    T get(const Coord c) {
      return get(c[0], c[1]);
    }

    T get(int x, int y) {
      return m_grid[x - m_mx].get()->at(y - m_my);
    }

    void checkExtents(const Coord c) {
      const int x = c[0], y = c[1];

      if (m_mx > m_px) {
        addPX();
        m_mx = m_px = x;
      }
      if (m_my > m_py) {
        addPY();
        m_my = m_py = y;
      }

      if (x > m_px) {
        for (int i = x - m_px; i > 0; i--) addAndFillPX();
        m_px = x;
      } else if (x < m_mx) {
        for (int i = m_mx - x; i > 0; i--) addAndFillMX();
        int tmp = m_mx;
        m_mx = x;
      }

      if (y > m_py) {
        for (int i = y - m_py; i > 0; i--) addPY();
        m_py = y;
      } else if (y < m_my) {
        for (int i = m_my - y; i > 0; i--) addMY();
        m_my = y;
      }
    }
};
