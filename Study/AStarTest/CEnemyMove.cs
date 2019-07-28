using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class CEnemyMove : MonoBehaviour {

    public CBoard _board;

    public int _index; //현재 타일위치.
    List<CTile> _list;
    CTile[,] _map;
    bool _isGoal = false;

    void Awake()
    {
        //_board = GameObject.Find("Tiles").GetComponent<CBoard>();
        _board = CBoard.GetInstance();
    }

    public void SetStartPosition(int pos)
    {
        //현재 타일의 위치를 리스트에서 구함.
        _list = _board.FindPath(pos);
        _map = _board._board;

        for (int i = 0 ; i < _list.Count ; i++)
        {
            if(_list[i] == _map[0,pos])
            {
                _index = i;
                break;
            }
        }

        StartCoroutine("MoveCoroutine");
    }

    IEnumerator MoveCoroutine()
    {
        while(!_isGoal)
        {
            Move();
            yield return new WaitForSeconds(0.1f);
        }
    }

    void Move()
    {
        //다음 목적지 (_list의 다음번호)의 위치로 이동

        if(_index != _list.Count-1)
        {
            transform.position = Vector3.MoveTowards(transform.position, _list[_index + 1].transform.position, 15f * Time.deltaTime);
            if (transform.position == _list[_index + 1].transform.position)
            {
                _index++;
            }
        }
        else
        {
            transform.Translate(Vector2.right * 15f * Time.deltaTime);
        }
    }

    void OnTriggerEnter2D(Collider2D col)
    {
        if(col.tag.Equals("Goal"))
        {
            _isGoal = true;
        }
    }
}