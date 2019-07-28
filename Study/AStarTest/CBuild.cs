using UnityEngine;
using System.Collections;

public class CBuild : MonoBehaviour {

    public GameObject _buildPanel;

    public GameObject _buildButton;
    public GameObject _buildMenu;
    public CBoard _board;

    void Awake()
    {
        _board = CBoard.GetInstance();
    }

	public void OnClickBuildButton()
    {
        //버튼은 비활성화하고 메뉴를 활성화함
        _buildButton.SetActive(false);  
        _buildMenu.SetActive(true);
    }

    public void OnClickTurret(string turretName)
    {
        StopCoroutine("BuildCoroutine");
        StartCoroutine("BuildCoroutine",turretName);
    }

    public void OnEscapeButtonClick()
    {
        _buildButton.SetActive(true);
        _buildMenu.SetActive(false);
    }

    IEnumerator BuildCoroutine(string turretName)
    {
        while(true)
        {
            if(Input.GetMouseButton(0))
            {
                Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);

                RaycastHit hit;

                if(Physics.Raycast(ray,out hit))
                {
                    int layer = hit.transform.gameObject.layer;

                    if(layer == LayerMask.NameToLayer("Tile"))
                    {
                        if (hit.transform.gameObject.GetComponent<CTile>()._isBuild)
                        {
                            _buildPanel.SetActive(true);
                        }
                        else
                        {

                        }
                    }
                }
            }   
        }
    }
}
