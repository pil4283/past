using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class CTile : MonoBehaviour {

    GameObject _building;
    
    public Vector2 _pos { get; set; }
    Renderer _renderer;

    public bool _isPath
    {
        get;
        set;
    }
    public bool _isBuild
    {
        get;
        set;
    }

    public Text _text;
    public int _g { get; set; }
    public int _h { get; set; }
    public int _f { get; set; }
    public string parent;

    public bool p;

    void Awake()
    {
        _isPath = true;
        p = _isPath;
        _renderer = GetComponent<Renderer>();
    }

    public void ChangeMaterial(bool isBuild)
    {
        _isBuild = isBuild;
        //
        if(isBuild)
        {
            _renderer.material.color = new Color(255f, 255f, 255f);
        }
        else
        {
            _renderer.material.color = new Color(0f, 0f, 0f);
        }
    }

    void AttachBuilding(GameObject obj)
    {
        _building = obj;
        ChangeMaterial(true);
    }

    void DeleteBuilding()
    {
        _building = null;
        ChangeMaterial(false);
    }

    public void RendererDisable()
    {
        _renderer.enabled = false;
    }

    public void RendererEnable()
    {
        _renderer.enabled = true;
    }
}