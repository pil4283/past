using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class CEnemyFSM : MonoBehaviour {

    CEnemyStat _stat;
    CEnemyAnimation _anim;
    NavMeshAgent _nav;
    
    public float _attackDist;

    [SerializeField]
    List<Transform> _playerUnit;

    [SerializeField]//test
    GameObject Target;

    void Awake()
    {
        _stat = GetComponent<CEnemyStat>();
        _anim = GetComponent<CEnemyAnimation>();
        _nav = GetComponent<NavMeshAgent>();
    }

	// Use this for initialization
	void Start () {
        _nav.Stop();

        StartCoroutine("EnemyFSMCoroutine");
	}

    //시작할때마다 매니저에서 유닛리스트를뽑아서 가져온 후 
    public void PlayerUnitPos(List<GameObject> units)
    {
        for(int i = 0 ; i < units.Count ; i++)
        {
            _playerUnit.Add(units[i].transform);
        }
    }
	
	IEnumerator EnemyFSMCoroutine()
    {
        //생성이되면 CREATE애니메이션이 재생됨(땅에서 올라오는 애니메이션)
        //CREATE애니메이션이 끝나기 전까지 행동 불가
        while (_stat._state == CEnemyStat.STATE.CREATE)
        {
            yield return null;
        }
        //죽기 전까지 아래의 행동을 반복
        while (_stat._state != CEnemyStat.STATE.DEATH)
        {
            //플레이어의 유닛이 하나도없을때 = 게임오버면 IDLE애니메이션 재생
            if (_playerUnit.Count == 0)
            {
                _anim.PlayAnimation(CEnemyStat.STATE.IDLE);
                yield break;
            }

            int targetNum = 0; //적이 쫒아갈 플레이어유닛 리스트의 번호
            float dist = 100.0f; //플레이어 유닛과의 거리

            for (int i = 0; i < _playerUnit.Count; i++)
            {
                float targetDist = Vector3.Distance(_playerUnit[i].position, transform.position);
                //자신과 제일 가까운 유닛을 찾아서 저장
                if (targetDist < dist)
                {
                    dist = targetDist;
                    targetNum = i;
                    Target = _playerUnit[targetNum].gameObject;
                }
            }

            //공격범위 안에 있을때
            if (dist <= _attackDist)
            {
                //이동을 멈추고 공격대상을 향해 공격애니메이션 재생
                _nav.Stop();
                Vector3 dir = _playerUnit[targetNum].position - transform.position;
                Quaternion rot = Quaternion.LookRotation(dir.normalized);
                transform.rotation = Quaternion.Slerp(transform.rotation, rot, 0.2f);
                _anim.PlayAnimation(CEnemyStat.STATE.ATTACK);
            }

            //공격범위 밖일때 
            else if (_attackDist < dist)
            {
                //처음 생성할때 멈춰두었던 네비게이션을 다시 실행
                _nav.SetDestination(_playerUnit[targetNum].position);
                _nav.Resume();
                //이동 애니메이션을 재생함
                _anim.PlayAnimation(CEnemyStat.STATE.MOVE);
            }
            yield return null;
        }

        //HP가 0이하면 플레이어유닛들의 적리스트에서 이 오브젝트를 삭제함
        for(int i = 0 ; i < _playerUnit.Count ; i++)
        {
            _nav.Stop();
            _playerUnit[i].SendMessage("DeleteEnemyList", gameObject);
        }
    }

    //플레이어의 유닛이 사망할경우 SendMessage로 실행. 
    void DeletePlayerList(GameObject unit)
    {
        _playerUnit.Remove(unit.transform);
    }
}
