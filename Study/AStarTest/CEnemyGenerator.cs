using UnityEngine;
using System.Collections;

public class CEnemyGenerator : MonoBehaviour{

    public Transform[] _genPos;
    public GameObject _enemy;

    // Use this for initialization
    void Start()
    {
        GameObject enemy;
        for(int i = 0 ; i < 5 ; i++)
        {
            enemy = Instantiate(_enemy, _genPos[i].position, Quaternion.identity) as GameObject;
            enemy.SendMessage("SetStartPosition", i);//나중에 수정
        }
    }
}