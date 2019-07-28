using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class CBoard : MonoBehaviour{

    public int _width;
    public int _height;
    public GameObject _tilePrefab;
    public CTile[,] _board;
    public List<GameObject> _tileList;

    public List<CTile> l;

    private static CBoard _instance;

    public static CBoard GetInstance()
    {
        return _instance;
    }

    void Awake()
    {
        _instance = this;
    }

    void Start()
    {
        CreateBoard();
    }

    void CreateBoard()
    {
        _board = new CTile[_width, _height];
        CTile t;

        for (int y = 0 ; y < _height ; y++)
        {
            for(int x = 0 ; x < _width ; x++)
            {
                //x = -9.3 _ 7.7 _ 6.1
                //y = 3.5 _ 1.9 _ 0.3
                GameObject tile = Instantiate(_tilePrefab, new Vector2((x * 1.6f) - 9.3f, 3.2f - (y * 1.6f)), Quaternion.identity) as GameObject;
                _tileList.Add(tile);
                tile.transform.parent = transform;

                t = tile.GetComponent<CTile>();
                t._pos = new Vector2(x, y);

                _board[x, y] = t;
            }
        }
        //l = FindPath(_tileList[0].GetComponent<CTile>(), _tileList[_tileList.Count - 46].GetComponent<CTile>());

        //l = FindPath(_tileList[0].GetComponent<CTile>(), _tileList[_tileList.Count-27].GetComponent<CTile>());

        for(int i = 0 ; i < l.Count ; i++)
        {
           l[i].GetComponent<Renderer>().material.color = new Color(255f, 255f, 255f);
        }
    }

    //건물이 깔릴경우 이동불가구역으로 설정
    public void TileBlock(int x,int y)
    {
        _board[x, y].ChangeMaterial(false);
        _board[x, y]._isPath = false;
    }

    public List<CTile> FindPatha(CTile start, CTile goal)
    {
        AStar a = new AStar();

        a.FindPath(start, goal, _board);

        return a.Path();
    }
    
    public List<CTile> FindPath(int yPos)
    {
        List<CTile> path = FindPatha(_tileList[12 * (yPos * 1)].GetComponent<CTile>(), _tileList[_tileList.Count - 25].GetComponent<CTile>());

        return path;
    }

}