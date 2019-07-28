using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class AStar {
    
    class Node
    {
        public int x;   //해당 노드 타일의 좌표
        public int y;

        public Node parent; //부모노드
        public List<Node> neighborList;
        public CTile tile;

        //비용
        public int g; //시작점부터 새로운 사각형까지의 비용
        public int h; //최종거리까지의 예상비용
        public int f; //g + h

        public Node(int x,int y, Node parent, CTile tile, int g, int h,int f)
        {
            this.x = x;
            this.y = y;
            this.parent = parent;
            this.tile = tile;
            this.g = g;
            this.h = h;
            this.f = f;
            neighborList = new List<Node>();
        }
    }

    CTile[,] _map;
    int _mapWidth;
    int _mapHeight;

    List<Node> _openList;   //열린노드
    List<Node> _closeList;  //닫힌노드
    List<Node> _finalPath;  //목표까지의 최종경로

    Node _start = null;
    Node _goal = null;

    public AStar()
    {
        _openList = new List<Node>();
        _closeList = new List<Node>();
        _finalPath = new List<Node>();
    }

    public void FindPath(CTile startTile, CTile goalTile, CTile[,] map)
    {
        _map = map;
        
        //맵 크기. 이웃노드 검색때 사용
        _mapWidth = map.GetLength(0) - 1;
        _mapHeight = map.GetLength(1) - 1;
        
        _start = new Node((int)startTile._pos.x, (int)startTile._pos.y, null, startTile, 0, 0, 0);//시작노드
        _goal = new Node((int)goalTile._pos.x, (int)goalTile._pos.y, null, goalTile, 0, 0, 0);//도착노드

        _openList.Add(_start);

        bool searching = true;
        bool pathExists = true;

        Node searchNode;

        while(searching && pathExists)
        {
            //비용이 제일 적은타일부터 검색시작
            searchNode = SearchBestNodeFromOpenList();
            if(searchNode == null)
            {
                //만약 하나도 없으면 목적지로 가는 길이 없으므로 루프문 빠져나옴
                pathExists = false;
                break;
            }
            _closeList.Add(searchNode);

            //목적지까지 도달하면 종료
            if (IsGoal(searchNode))
            {
                _goal = searchNode;
                searching = false;
            }
            else
            {
                AddNeighborNodeToOpenList(searchNode);
            }

            
        }

        if(pathExists)
        {
            AddFinalPath(_goal);
        }
        else
        {
            //길이 막혔으니 뚫으라는 메세지
        }
    }

    //가장 F값이 적은 노드를 찾음.
    Node SearchBestNodeFromOpenList()
    {
        int minF = int.MaxValue;
        Node bestNode = null;

        foreach(Node n in _openList)
        {
            if (n.f < minF)
            { 
                minF = n.f;
                bestNode = n;
            }
        }
        if(bestNode != null)
        {
            //열린목록에서 삭제하여 무한루프에 빠지지않게함.
            _openList.Remove(bestNode);
        }

        return bestNode;
    }

    void AddFinalPath(Node n)
    {
        _finalPath.Add(n);
        while (true)
        {
            _finalPath.Add(n.parent);
            n = n.parent;
            if(n.parent == null)
            {
                break;
            }
        }
    }

    void AddNeighborNodeToOpenList(Node n)
    {
        //12시부터 시계방향으로 검색 직선방향부터 구하고 그 다음 대각선
        //주변타일이 존재하는 타일인지(배열안에 있는지), 통과가능한 타일인지 검색
        //맞다면 해당 노드를 OpenList에 추가 후 n을 부모노드로 지정함

        //_neighborList.Clear();
        Node neighbor;

        //12
        if (0 <= n.y - 1 && _map[n.x, n.y - 1]._isPath && !IsCloseNode(n, 0, -1))
        {
            neighbor = NewNodeFromParent(n, 0, -1);
            n.neighborList.Add(neighbor);
        }

        //3
        if (n.x + 1 <= _mapWidth && _map[n.x + 1, n.y]._isPath && !IsCloseNode(n, +1, 0)) 
        {
            neighbor = NewNodeFromParent(n, +1, 0);
            n.neighborList.Add(neighbor);
        }

        //6
        if (n.y + 1 <= _mapHeight && _map[n.x, n.y + 1]._isPath && !IsCloseNode(n, 0, +1))
        {
            neighbor = NewNodeFromParent(n, 0, +1);
            n.neighborList.Add(neighbor);
        }

        //9
        if (0 <= n.x - 1 && _map[n.x - 1, n.y]._isPath && !IsCloseNode(n, -1, 0))
        {
            neighbor = NewNodeFromParent(n, -1, 0);
            n.neighborList.Add(neighbor);
        }

        //대각선
        //1:30
        if ((((n.x + 1 <= _mapWidth) && (0 <= n.y - 1))) && _map[n.x + 1, n.y - 1]._isPath && !IsCloseNode(n, +1, -1)) 
        {
            neighbor = NewNodeFromParent(n, +1, -1);
            n.neighborList.Add(neighbor);
        }

        //4:30
        if ((((n.x + 1 <= _mapWidth) && (n.y + 1 <= _mapHeight))) && _map[n.x + 1, n.y + 1]._isPath && !IsCloseNode(n, +1, +1))
        {
            neighbor = NewNodeFromParent(n, +1, +1);
            n.neighborList.Add(neighbor);
        }

        //7:30
        if ((((0 <= n.x - 1) && (n.y + 1 <= _mapHeight))) && _map[n.x - 1, n.y + 1]._isPath && !IsCloseNode(n, -1, +1))
        {
            neighbor = NewNodeFromParent(n, -1, +1);
            n.neighborList.Add(neighbor);
        }

        //10:30
        if ((((0 <= n.x - 1) && (0 <= n.y -1))) && _map[n.x - 1, n.y - 1]._isPath && !IsCloseNode(n, -1, -1))
        {
            neighbor = NewNodeFromParent(n, -1, -1);
            n.neighborList.Add(neighbor);
        }
    }

    Node NewNodeFromParent(Node n, int x, int y)
    {
        Node nn = null;
        
        if (IsOpenNode(n, x, y))
        {
            nn = FindNode(n, x, y);
            if (n.g + MovementCost(n.x + x, n.y + y) < nn.g)
            {
                nn.g = n.g + MovementCost(n.x + x, n.y + y);
                nn.f = nn.g + nn.h;

                nn.parent = n;

                _map[nn.x, nn.y]._g = nn.g;
                _map[nn.x, nn.y]._f = nn.f;
                _map[nn.x, nn.y]._h = nn.h;
                _map[nn.x, nn.y].parent = nn.parent.x.ToString() + " " + nn.parent.y.ToString();

                return nn;
            }
        }
        else
        {
            Node newNode = new Node(n.x + x, n.y + y, n, _map[n.x + x, n.y + y], 0, 0, 0);

            newNode.g = n.g + MovementCost(x, y);
            newNode.h = Manhattan(newNode);
            newNode.f = newNode.g + newNode.h;

            newNode.parent = n;

            _map[newNode.x, newNode.y]._g = newNode.g;
            _map[newNode.x, newNode.y]._h = newNode.h;
            _map[newNode.x, newNode.y]._f = newNode.f;
            _map[newNode.x, newNode.y].parent = newNode.parent.x.ToString() + " " + newNode.parent.y.ToString();

            _openList.Add(newNode);

            return newNode;
        }
        return null;
    }

    //이동비용 계산, 직선10, 대각선은14
    int MovementCost(int x,int y)
    {
        //둘중 하나가 0이면 직선이므로 10 그 외는 14
        if(x == 0 || y == 0)
        {
            return 10;
        }
        else
        {
            return 14;
        }
    }

    //h비용 구하기
    int Manhattan(Node n)
    {
        return (Mathf.Abs(n.x - _goal.x) + Mathf.Abs(n.y - _goal.y)) * 10; ;
    }

    bool IsGoal(Node n)
    {
        if(n.x == _goal.x && n.y == _goal.y)
        {
            return true;
        }
        return false;
    }

    public List<CTile> Path()
    {
        List<CTile> path = new List<CTile>();

        foreach (Node n in _finalPath)
        {
            path.Add(n.tile);
        }

        if (path.Count != 0)
        {
            path.Reverse();
        }

        return path;
    }

    Node FindNode(Node n, int x, int y)
    {
        foreach(Node nn in _openList)
        {
            if(nn.x == n.x + x && nn.y == n.y + y)
            {
                return nn;
            }
        }
        return null;
    }

    //해당 노드가 열린노드인지 아닌지 찾음
    Node FindInOpenList(Node n)
    {
        foreach(Node nn in _openList)
        {
            //좌표로 확인
            if(nn.x == n.x && nn.y == n.y)
            {
                //열린노드라면 해당노드 반환
                return nn;
            }
        }
        //아니라면 널값 반환
        return null;
    }

    //해당 노드가 닫힌노드인지 아닌지 찾음
    Node FindInCloseList(Node n)
    {
        foreach (Node nn in _closeList)
        {
            //좌표로 확인
            if (nn.x == n.x && nn.y == n.y)
            {
                //닫힌노드라면 해당노드 반환
                return nn;
            }
        }
        //아니라면 널값 반환
        return null;
    }

    //이웃노드가 닫힌노드인지, 열린노드인지 확인용
    bool IsCloseNode(Node n, int x, int y)
    {
        foreach(Node nn in _closeList)
        {
            if (nn.x == n.x + x && nn.y == n.y + y) 
            {
                return true;
            }
        }

        return false;
    }

    bool IsOpenNode(Node n, int x, int y)
    {
        foreach (Node nn in _openList)
        {
            if (nn.x == n.x + x && nn.y == n.y + y)
            {
                return true;
            }
        }

        return false;
    }

}

