using UnityEngine;
using System.Collections;
using System.Collections.Generic;

/// <summary>
/// 
/// AStar
/// 
/// </summary>

public class CFindWay {

    class Node
    {
        public int x;
        public int y;
        public float G;
        public float H;
        public float F;
        public Node parent;
        public CTile tile;
        public Node(int x, int y, float G, float H, float F, Node parent, CTile tile)
        {
            this.x = x;
            this.y = y;
            this.G = G;
            this.H = H;
            this.F = F;
            this.parent = parent;
            this.tile = tile;
        }
    }

    List<Node> openList;
    List<Node> closeList;
    List<Node> neighbours;
    List<Node> finalPath;
    Node start;
    Node end;

    CTile[,] map;
    int mapWidth;
    int mapHeight;

    public CFindWay()
    {
        openList = new List<Node>();
        closeList = new List<Node>();
        neighbours = new List<Node>();
        finalPath = new List<Node>();
    }

    public void FindPath(CTile startTile, CTile goalTile, CTile[,] map, bool targetTileMustBeFree)
    {
        this.map = map;
        this.mapWidth = map.GetLength(0);
        this.mapHeight = map.GetLength(1);

        start = new Node((int)startTile._pos.x, (int)startTile._pos.y, 0, 0, 0, null, startTile);
        end = new Node((int)goalTile._pos.x, (int)goalTile._pos.y, 0, 0, 0, null, goalTile);

        openList.Add(start);
        bool keepSearching = true;
        bool pathExists = true;

        while((keepSearching) && (pathExists))
        {
            Node currentNode = ExtractBestNodeFromOpenList();
            if(currentNode == null)
            {
                pathExists = false;
                break;
            }

            closeList.Add(currentNode);

            //마지막(목적지)노드인가
            if(NodeIsGoal(currentNode))
            {
                keepSearching = false;
            }
            else
            {
                if(targetTileMustBeFree)
                {
                    FindValidFourNeighbours(currentNode);
                }
                else
                {
                    FindValidFourNeighboursIgnoreTargetTile(currentNode);
                }

                foreach(Node neighbour in neighbours)
                {
                    //이웃 노드중에 닫힌노드가 아닌것을 검색한 뒤...
                    if(FindInCloseList(neighbour) != null)
                    {
                        continue;
                    }

                    //이웃 노드가 열린노드인지 검색
                    Node inOpenList = FindInOpenList(neighbour);
                    if(inOpenList == null)
                    {
                        //이웃 노드가 닫힌것도,열린것도 아니라면 처음발견된것이므로 열린노드에 추가
                        openList.Add(neighbour);
                    }
                    else
                    {
                        //이웃 노드가 열린거라면 이미 한번 발견된것이므로 다시 계산을 해봄
                        if (neighbour.G < inOpenList.G)
                        {
                            inOpenList.G = neighbour.G;
                            inOpenList.F = inOpenList.G + inOpenList.H;
                            inOpenList.parent = currentNode;
                        }
                    }
                }
            }
        }

        if(pathExists)
        {
            Node n = FindInCloseList(end);
            while(n != null)
            {
                finalPath.Add(n);
                n = n.parent;
            }
        }
    }

    //목표지점까지의 노드를 구함
    public List<int> PointsFromPath()
    {
        List<int> points = new List<int>();
        foreach (Node n in finalPath)
        {
            points.Add(n.x);
            points.Add(n.y);
        }
        return points;
    }

    public List<CTile> TilesFromPath()
    {
        List<CTile> path = new List<CTile>();
        foreach(Node n in finalPath)
        {
            path.Add(n.tile);
        }

        if (path.Count != 0)
        {
            path.Reverse();
            path.RemoveAt(0);
        }
        return path;
    }

    //최단거리 찾기
    Node ExtractBestNodeFromOpenList()
    {
        float minF = float.MaxValue;
        Node bestOne = null;

        foreach(Node n in openList)
        {
            if(n.F < minF)
            {
                bestOne = n;
            }
        }
        if(bestOne != null)
        {
            openList.Remove(bestOne);
        }
        return bestOne;
    }

    bool NodeIsGoal(Node node)
    {
        return ((node.x == end.x) && node.y == end.y);
    }

    void FindValidFourNeighbours(Node n)
    {
        neighbours.Clear();
        
        //위쪽
        if (n.y - 1 >= 0 && map[n.x, n.y - 1]._isPath) 
        {
            Node vn = PrepareNewNodeFrom(n, 0, -1);
            neighbours.Add(vn);
        }
        
        //아래쪽
        if(n.y+1 <= mapHeight - 1 && map[n.x,n.y+1]._isPath)
        {
            Node vn = PrepareNewNodeFrom(n, 0, +1);
            neighbours.Add(vn);
        }

        //왼쪽
        if (n.x - 1 >= 0 && map[n.x - 1, n.y]._isPath) 
        {
            Node vn = PrepareNewNodeFrom(n, -1, 0);
            neighbours.Add(vn);
        }

        if(n.x+1 <= mapWidth -1 && map[n.x+1,n.y]._isPath)
        {
            Node vn = PrepareNewNodeFrom(n, +1, 0);
            neighbours.Add(vn);
        }
    }

    void FindValidFourNeighboursIgnoreTargetTile(Node n)
    {
        neighbours.Clear();

        if ((n.y - 1 >= 0 && map[n.x, n.y - 1]._isPath) || (map[n.x, n.y - 1] == end.tile)) 
        {
            Node vn = PrepareNewNodeFrom(n, 0, -1);
            neighbours.Add(vn);
        }

        if ((n.y + 1 <= mapHeight - 1 && map[n.x, n.y + 1]._isPath) || (map[n.x, n.y + 1] == end.tile))
        {
            Node vn = PrepareNewNodeFrom(n, 0, +1);
            neighbours.Add(vn);
        }

        if ((n.x - 1 >= 0 && map[n.x - 1, n.y]._isPath) || (map[n.x - 1, n.y] == end.tile))
        {
            Node vn = PrepareNewNodeFrom(n, -1, 0);
            neighbours.Add(vn);
        }

        if ((n.y + 1 <= mapWidth - 1 && map[n.x + 1, n.y]._isPath) || (map[n.x + 1, n.y] == end.tile))
        {
            Node vn = PrepareNewNodeFrom(n, +1, 0);
            neighbours.Add(vn);
        }
    }

    Node PrepareNewNodeFrom(Node n, int x,int y)
    {
        Node newNode = new Node(n.x + x, n.y + y, 0, 0, 0, n, map[n.x + x, n.y + y]);

        newNode.G = n.G + MovementCost(n, newNode);
        newNode.H = Heuristic(newNode);
        newNode.F = newNode.G + newNode.H;

        newNode.parent = n;

        return newNode;
    }

    float Heuristic(Node n)
    {
        return Mathf.Sqrt((n.x - end.x) * (n.x - end.x) + (n.y - end.y) * (n.y - end.y));
    }

    float MovementCost(Node a, Node b)
    {
        //return map[b.x, b.y].MovementCost();
        return 1;
    }

    Node FindInCloseList(Node n)
    {
        foreach(Node nn in closeList)
        {
            if((nn.x == n.x) && (nn.y == n.y))
            {
                return nn;
            }
        }
        return null;
    }

    Node FindInOpenList(Node n)
    {
        foreach(Node nn in openList)
        {
            if((nn.x == n.x) && (nn.y == n.y))
            {
                return nn;
            }
        }
        return null;
    }
}
