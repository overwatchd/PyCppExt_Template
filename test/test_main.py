import pytest
import PyCppExt

def test_version():
    assert PyCppExt.version()


if __name__ == '__main__':
    pytest.main()
